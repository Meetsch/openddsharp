﻿/*********************************************************************
This file is part of OpenDDSharp.

OpenDDSharp is a .NET wrapper for OpenDDS.
Copyright (C) 2018 Jose Morato

OpenDDSharp is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenDDSharp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OpenDDSharp. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
using System;
using System.IO;
using System.Diagnostics;
using System.ComponentModel;
using OpenDDSharp.Test;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace OpenDDSharp.UnitTest.Helpers
{
    internal class SupportProcessHelper
    {
        #region Constants
        private const string DEBUG_TARGET_FOLDER = @"Debug\";
        private const string RELEASE_TARGET_FOLDER = @"Release\";
        private const string SIXTY_FOUR_PLATFORM_FOLDER = @"x64\";
        private const string EIGHTY_SIX_PLATFORM_FOLDER = @"x86\";
        private const string TEST_SUPPORT_PROCESS_PATH = @"..\..\..\..\TestSupportProcess\bin\";
        private const string TEST_SUPPORT_PROCESS_EXE_NAME = @"TestSupportProcess.exe";
        private const string DCPSINFOREPO_PROCESS_EXE_NAME = @"DCPSInfoRepo.exe";
        #endregion

        #region Fields
        private string _platformFolder;        
        private string _targetFolder;
        private TestContext _testContext;
        #endregion

        #region Constructors
        public SupportProcessHelper(TestContext testContext)
        {
            _testContext = testContext;
            _platformFolder = SIXTY_FOUR_PLATFORM_FOLDER;
            _targetFolder = RELEASE_TARGET_FOLDER;
            SetEightySixPlatform();
            SetDebugTarget();
        }
        #endregion

        #region Methods
        public Process SpawnSupportProcess(SupportTestKind teskKind)
        {
            string supportProcessPath = Path.Combine(TEST_SUPPORT_PROCESS_PATH, _platformFolder, _targetFolder, TEST_SUPPORT_PROCESS_EXE_NAME);
            if (!File.Exists(supportProcessPath))
            {
                _testContext.WriteLine($"The support process executable could not be located at {supportProcessPath}.");
                throw new FileNotFoundException($"The support process executable could not be located at {supportProcessPath}.");
            }

            return SpawnProcess(supportProcessPath, teskKind.ToString());            
        }

        public Process SpawnDCPSInfoRepo()
        {
            string ddsPath = Environment.GetEnvironmentVariable("DDS_ROOT");
            string infoRepoPath = Path.Combine(ddsPath, "bin_" + _platformFolder, DCPSINFOREPO_PROCESS_EXE_NAME);
            if (!File.Exists(infoRepoPath))
            {
                _testContext.WriteLine($"The support process executable could not be located at {infoRepoPath}.");
                throw new FileNotFoundException($"The support process executable could not be located at {infoRepoPath}.");
            }

            return SpawnProcess(infoRepoPath, string.Empty);
        }

        private Process SpawnProcess(string path, string arguments)
        {
            ProcessStartInfo processInfo = new ProcessStartInfo(path)
            {
                Arguments = arguments,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                CreateNoWindow = true,
                UseShellExecute = false,
            };

            Process infoRepoProcess = new Process
            {
                StartInfo = processInfo,
                EnableRaisingEvents = true
            };

            infoRepoProcess.OutputDataReceived += SupportProcessOnOutputDataReceived;
            infoRepoProcess.ErrorDataReceived += SupportProcessOnErrorDataReceived;

            bool processStarted = false;
            try
            {
                processStarted = infoRepoProcess.Start();
            }
            catch (Win32Exception e)
            {
                if (File.Exists(path))
                {
                    _testContext.WriteLine($"The support process executable at {path} could not be executed.");
                    throw new FileNotFoundException($"The support process executable at {path} could not be executed.", e);
                }
                _testContext.WriteLine($"The support process executable can not be located at {path}.");
                throw new InvalidOperationException($"The support process executable can not be located at {path}.", e);
            }

            if (!processStarted)
            {
                throw new InvalidOperationException("Support process could not be started.");
            }

            infoRepoProcess.BeginOutputReadLine();
            infoRepoProcess.BeginErrorReadLine();

            return infoRepoProcess;
        }

        public void KillProcess(Process process)
        {
            if (!process.HasExited)
            {                
                process.Kill();
            }

            process.OutputDataReceived -= SupportProcessOnOutputDataReceived;
            process.ErrorDataReceived -= SupportProcessOnErrorDataReceived;
            process.Dispose();
        }

        private void SupportProcessOnOutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(e.Data))
            {
                _testContext.WriteLine(e.Data);
            }
        }

        private void SupportProcessOnErrorDataReceived(object sender, DataReceivedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(e.Data))
            {
                _testContext.WriteLine(e.Data);
            }
        }

        [Conditional("X86")]
        private void SetEightySixPlatform()
        {
            _platformFolder = EIGHTY_SIX_PLATFORM_FOLDER;
        }

        [Conditional("DEBUG")]
        private void SetDebugTarget()
        {
            _targetFolder = DEBUG_TARGET_FOLDER;
        }
        #endregion
    }
}
