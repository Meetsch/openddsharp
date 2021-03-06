//------------------------------------------------------------------------------
// <auto-generated>
// WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.
// DDS version: 3.13.1
// ACE version: 6.2a_p15
// Running on input file: TestMessage.idl
// </auto-generated>
//------------------------------------------------------------------------------

#pragma once

#pragma unmanaged
#include <dds/DCPS/Service_Participant.h>
#include "TestMessageTypeSupportImpl.h"
#pragma managed

#include <vcclr.h>
#include <msclr/marshal.h>
#include "LNK4248.h"

using namespace System::Collections::Generic;

// Incomplete types generate LNK4248 warnings when compiled for .NET
SUPPRESS_LNK4248_CORBA

namespace OpenDDSharp {
namespace HelloWorld {

    public ref class Message {

    private:
        System::String^ m_Content;

    public:
        property System::String^ Content {
            System::String^ get();
            void set(System::String^ value);
        }

    public:
        Message();

    internal:
        ::HelloWorld::Message ToNative();
        void FromNative(::HelloWorld::Message native);
    };

    public ref class MessageTypeSupport {

	private:
		msclr::interop::marshal_context context;
        static ::HelloWorld::MessageTypeSupport_ptr impl_entity;

	public:
		MessageTypeSupport();
		System::String^ GetTypeName();
		OpenDDSharp::DDS::ReturnCode RegisterType(::OpenDDSharp::DDS::DomainParticipant^ participant, System::String^ typeName);
        OpenDDSharp::DDS::ReturnCode UnregisterType(::OpenDDSharp::DDS::DomainParticipant^ participant, System::String^ typeName);

	};

///////////////////////////////////////////////////////////////////////

	public ref class MessageDataWriter : OpenDDSharp::DDS::DataWriter {

	private:
		::HelloWorld::MessageDataWriter_ptr impl_entity;

	public:
		MessageDataWriter(::OpenDDSharp::DDS::DataWriter^ dataWriter);
        OpenDDSharp::DDS::InstanceHandle RegisterInstance(Message^ instance);
        OpenDDSharp::DDS::InstanceHandle RegisterInstance(Message^ instance, OpenDDSharp::DDS::Timestamp timestamp);
        OpenDDSharp::DDS::ReturnCode UnregisterInstance(Message^ data);
		OpenDDSharp::DDS::ReturnCode UnregisterInstance(Message^ data, OpenDDSharp::DDS::InstanceHandle handle);
        OpenDDSharp::DDS::ReturnCode UnregisterInstance(Message^ data,OpenDDSharp::DDS::InstanceHandle handle, OpenDDSharp::DDS::Timestamp timestamp);
		OpenDDSharp::DDS::ReturnCode Write(Message^ data);
        OpenDDSharp::DDS::ReturnCode Write(Message^ data, OpenDDSharp::DDS::InstanceHandle handle);
        OpenDDSharp::DDS::ReturnCode Write(Message^ data, OpenDDSharp::DDS::InstanceHandle handle, OpenDDSharp::DDS::Timestamp timestamp);
		OpenDDSharp::DDS::ReturnCode Dispose(Message^ data);
		OpenDDSharp::DDS::ReturnCode Dispose(Message^ data, OpenDDSharp::DDS::InstanceHandle handle);
        OpenDDSharp::DDS::ReturnCode Dispose(Message^ data, OpenDDSharp::DDS::InstanceHandle handle, OpenDDSharp::DDS::Timestamp timestamp);
        OpenDDSharp::DDS::ReturnCode GetKeyValue(Message^ data, OpenDDSharp::DDS::InstanceHandle handle);
        System::Int32 LookupInstance(Message^ instance);
	};

///////////////////////////////////////////////////////////////////////

	public ref class MessageDataReader : OpenDDSharp::DDS::DataReader {

	private:
		::HelloWorld::MessageDataReader_ptr impl_entity;

	public:
		MessageDataReader(::OpenDDSharp::DDS::DataReader^ dataReader);

        OpenDDSharp::DDS::ReturnCode Read(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo);

		OpenDDSharp::DDS::ReturnCode Read(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
										  System::Int32 maxSamples);

        OpenDDSharp::DDS::ReturnCode Read(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
										  System::Int32 maxSamples,
										  OpenDDSharp::DDS::ReadCondition^ condition);

        OpenDDSharp::DDS::ReturnCode Read(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
										  System::Int32 maxSamples,
										  OpenDDSharp::DDS::SampleStateMask sampleStates,
										  OpenDDSharp::DDS::ViewStateMask viewStates,
										  OpenDDSharp::DDS::InstanceStateMask instanceStates);

        OpenDDSharp::DDS::ReturnCode Take(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo);

		OpenDDSharp::DDS::ReturnCode Take(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
										  System::Int32 maxSamples);

        OpenDDSharp::DDS::ReturnCode Take(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
										  System::Int32 maxSamples,
										  OpenDDSharp::DDS::ReadCondition^ condition);        

        OpenDDSharp::DDS::ReturnCode Take(List<Message^>^ receivedData,
										  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
										  System::Int32 maxSamples,
										  OpenDDSharp::DDS::SampleStateMask sampleStates,
										  OpenDDSharp::DDS::ViewStateMask viewStates,
										  OpenDDSharp::DDS::InstanceStateMask instanceStates);
        
        OpenDDSharp::DDS::ReturnCode ReadInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												  OpenDDSharp::DDS::InstanceHandle handle);

		OpenDDSharp::DDS::ReturnCode ReadInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												  OpenDDSharp::DDS::InstanceHandle handle,
												  System::Int32 maxSamples);

		OpenDDSharp::DDS::ReturnCode ReadInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												  OpenDDSharp::DDS::InstanceHandle handle,
												  System::Int32 maxSamples,
												  OpenDDSharp::DDS::ReadCondition^ condition);

        OpenDDSharp::DDS::ReturnCode ReadInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,												  
												  OpenDDSharp::DDS::InstanceHandle handle,
                                                  System::Int32 maxSamples,
												  OpenDDSharp::DDS::SampleStateMask sampleStates,
												  OpenDDSharp::DDS::ViewStateMask viewStates,
												  OpenDDSharp::DDS::InstanceStateMask instanceStates);

        OpenDDSharp::DDS::ReturnCode TakeInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												  OpenDDSharp::DDS::InstanceHandle handle);

		OpenDDSharp::DDS::ReturnCode TakeInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												  OpenDDSharp::DDS::InstanceHandle handle,
												  System::Int32 maxSamples);

		OpenDDSharp::DDS::ReturnCode TakeInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												  OpenDDSharp::DDS::InstanceHandle handle,
												  System::Int32 maxSamples,
												  OpenDDSharp::DDS::ReadCondition^ condition);

        OpenDDSharp::DDS::ReturnCode TakeInstance(List<Message^>^ receivedData,
												  List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												  OpenDDSharp::DDS::InstanceHandle handle,
												  System::Int32 maxSamples,
												  OpenDDSharp::DDS::SampleStateMask sampleStates,
												  OpenDDSharp::DDS::ViewStateMask viewStates,
												  OpenDDSharp::DDS::InstanceStateMask instanceStates);

        OpenDDSharp::DDS::ReturnCode ReadNextInstance(List<Message^>^ receivedData,
												      List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												      OpenDDSharp::DDS::InstanceHandle previousHandle);

		OpenDDSharp::DDS::ReturnCode ReadNextInstance(List<Message^>^ receivedData,
												      List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												      OpenDDSharp::DDS::InstanceHandle previousHandle,
												      System::Int32 maxSamples);

		OpenDDSharp::DDS::ReturnCode ReadNextInstance(List<Message^>^ receivedData,
												      List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												      OpenDDSharp::DDS::InstanceHandle previousHandle,
												      System::Int32 maxSamples,
												      OpenDDSharp::DDS::ReadCondition^ condition);

        OpenDDSharp::DDS::ReturnCode ReadNextInstance(List<Message^>^ receivedData,
												      List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												      OpenDDSharp::DDS::InstanceHandle previousHandle,
												      System::Int32 maxSamples,
												      OpenDDSharp::DDS::SampleStateMask sampleStates,
												      OpenDDSharp::DDS::ViewStateMask viewStates,
												      OpenDDSharp::DDS::InstanceStateMask instanceStates);

         OpenDDSharp::DDS::ReturnCode TakeNextInstance(List<Message^>^ receivedData,
												       List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												       OpenDDSharp::DDS::InstanceHandle previousHandle);

		OpenDDSharp::DDS::ReturnCode TakeNextInstance(List<Message^>^ receivedData,
												      List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												      OpenDDSharp::DDS::InstanceHandle previousHandle,
												      System::Int32 maxSamples);

		OpenDDSharp::DDS::ReturnCode TakeNextInstance(List<Message^>^ receivedData,
												      List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												      OpenDDSharp::DDS::InstanceHandle previousHandle,
												      System::Int32 maxSamples,
												      OpenDDSharp::DDS::ReadCondition^ condition);

        OpenDDSharp::DDS::ReturnCode TakeNextInstance(List<Message^>^ receivedData,
												      List<::OpenDDSharp::DDS::SampleInfo^>^ receivedInfo,
												      OpenDDSharp::DDS::InstanceHandle previousHandle,
												      System::Int32 maxSamples,
												      OpenDDSharp::DDS::SampleStateMask sampleStates,
												      OpenDDSharp::DDS::ViewStateMask viewStates,
												      OpenDDSharp::DDS::InstanceStateMask instanceStates);

		OpenDDSharp::DDS::ReturnCode ReadNextSample(Message^ data, ::OpenDDSharp::DDS::SampleInfo^ sampleInfo);

		OpenDDSharp::DDS::ReturnCode TakeNextSample(Message^ data, ::OpenDDSharp::DDS::SampleInfo^ sampleInfo);

        OpenDDSharp::DDS::ReturnCode GetKeyValue(Message^ data, OpenDDSharp::DDS::InstanceHandle handle);

        OpenDDSharp::DDS::InstanceHandle LookupInstance(Message^ instance);
	};

///////////////////////////////////////////////////////////////////////
};
};
