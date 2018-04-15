﻿using System;
using System.IO;
using System.Xml;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;
using EnvDTE;
using EnvDTE80;
using System.Runtime.InteropServices;

namespace OpenDDSharp.BuildTasks
{    
    public class GenerateNativeProjectTask : Task
    {
        #region Fields
        private DTE2 _dte;
        private Solution2 _solution;
        private Project _project;
        private string _solutionName;
        private string _projectName;
        #endregion

        #region Properties
        [Required]
        public string OriginalProjectName { get; set; }

        [Required]
        public string IntDir { get; set; }

        [Required]
        public string TemplatePath { get; set; }

        [Required]
        public ITaskItem[] IdlFiles { get; set; }

        [Required]
        public string Configuration { get; set; }

        [Required]
        public string Platform { get; set; }       
        #endregion

        #region Methods
        [STAThread]
        public override bool Execute()
        {
            Log.LogMessage(MessageImportance.High, "Generating native IDL library...");

            Initialize();
            GenerateSolutionFile();
            GenerateProjectFile();
            CopyIdlFiles();
            BuildWithMSBuild();
            ShutDown();

            return true;
        }       

        private void Initialize()
        {
            _solutionName = OriginalProjectName + "NativeSolution";
            _projectName = OriginalProjectName + "Native";

            Type type = Type.GetTypeFromProgID("VisualStudio.DTE.15.0");
            Object obj = Activator.CreateInstance(type, true);
            _dte = (DTE2)obj;
        }

        private void GenerateSolutionFile()
        {           
            _dte.Solution.Create(IntDir, _solutionName);
            _solution = (Solution2)_dte.Solution;
        }

        private void GenerateProjectFile()
        {
            int retry = 100;
            bool success = false;

            while (!success && retry > 0)
            {
                try
                {
                    if (_project != null)
                        _solution.Remove(_project);

                    _solution.AddFromTemplate(TemplatePath, IntDir, _projectName);
                    _project = _solution.Projects.Item(1);

                    foreach (ITaskItem s in IdlFiles)
                    {
                        string filename = s.GetMetadata("Filename");

                        _project.ProjectItems.AddFromFile(filename + "C.h");
                        _project.ProjectItems.AddFromFile(filename + "IDL_Export.h");
                        _project.ProjectItems.AddFromFile(filename + "S.h");
                        _project.ProjectItems.AddFromFile(filename + "TypeSupportC.h");
                        _project.ProjectItems.AddFromFile(filename + "TypeSupportImpl.h");
                        _project.ProjectItems.AddFromFile(filename + "TypeSupportS.h");

                        _project.ProjectItems.AddFromFile(filename + "C.cpp");
                        _project.ProjectItems.AddFromFile(filename + "S.cpp");
                        _project.ProjectItems.AddFromFile(filename + "TypeSupportC.cpp");
                        _project.ProjectItems.AddFromFile(filename + "TypeSupportImpl.cpp");
                        _project.ProjectItems.AddFromFile(filename + "TypeSupportS.cpp");

                        _project.ProjectItems.AddFromFile(filename + "C.inl");
                        _project.ProjectItems.AddFromFile(filename + "TypeSupportC.inl");
                    }
                    _project.Save();

                    // No really elegant but I couldn't cast the project to VCProject because the "Interface not registered" and M$ says that it is not a bug :S
                    // https://developercommunity.visualstudio.com/content/problem/568/systeminvalidcastexception-unable-to-cast-com-obje.html
                    XmlDocument doc = new XmlDocument();
                    doc.Load(_project.FullName);
                    XmlNode root = doc.DocumentElement;
                    XmlNamespaceManager ns = new XmlNamespaceManager(doc.NameTable);
                    ns.AddNamespace("msbld", "http://schemas.microsoft.com/developer/msbuild/2003");
                    XmlNodeList nodes = root.SelectNodes("//msbld:PreprocessorDefinitions", ns);
                    foreach (XmlNode node in nodes)
                    {
                        foreach (ITaskItem s in IdlFiles)
                        {
                            string fileName = s.GetMetadata("Filename");
                            node.InnerXml = string.Format("{0}IDL_BUILD_DLL;{1}", fileName.ToUpper(), node.InnerXml);
                        }
                    }
                    doc.Save(_project.FullName);
                    success = true;
                }
                catch (COMException)
                {
                    success = false;
                    retry--;
                    
                    if (retry > 0)
                        System.Threading.Thread.Sleep(150);
                    else
                        throw;                    
                }
            }            
        }

        private void CopyIdlFiles()
        {            
            foreach (ITaskItem s in IdlFiles)
            {
                string identity = s.GetMetadata("Identity");
                string inputPath = s.GetMetadata("FullPath");                
                string outputPath = Path.Combine(IntDir, identity);

                using (StreamReader reader = new StreamReader(inputPath))
                using (StreamWriter writer = new StreamWriter(outputPath))
                {
                    writer.WriteLine("#include <tao/orb.idl> // Workaround for the error C2961: inconsistent explicit instantiations, a previous explicit instantiation did not specify '__declspec(dllimport)'");
                    while (!reader.EndOfStream)
                    {
                        writer.WriteLine(reader.ReadLine());
                    }

                    writer.Flush();

                    writer.Close();
                    reader.Close();
                }
            }
        }

        private void BuildWithMSBuild()
        {
            if (Platform == "Win32")
                Platform = "x86";

            string solutionConfiguration = string.Format("{0}|{1}", Configuration, Platform);

            int retry = 100;
            bool success = false;

            while (!success && retry > 0)
            {
                try
                {
                    _solution.SolutionBuild.BuildProject(solutionConfiguration, _project.FullName, true);
                    success = true;
                }
                catch (COMException)
                {
                    success = false;
                    retry--;

                    if (retry > 0)
                        System.Threading.Thread.Sleep(150);
                    else
                        throw;
                }
            }
        }

        private void ShutDown()
        {
            _dte.Quit();            
        }
        #endregion
    }
}
