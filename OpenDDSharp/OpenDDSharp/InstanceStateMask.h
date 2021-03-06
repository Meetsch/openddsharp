/*********************************************************************
This file is part of OpenDDSharp.

OpenDDSharp is a .NET wrapper for OpenDDS
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
#pragma once

#pragma unmanaged 
#include <dds\DdsDcpsInfrastructureC.h>
#pragma managed

namespace OpenDDSharp {
	namespace DDS {

		value struct InstanceStateKind;
		 
		/// <summary>
		/// Represent a bit-mask of <see cref="InstanceStateKind" />
		/// </summary>
		public value struct InstanceStateMask {

		public:
			/// <summary>
			/// A mask containing any <see cref="InstanceStateKind" />
			/// </summary>
			static const InstanceStateMask AnyInstanceState = ::DDS::ANY_INSTANCE_STATE;

			/// <summary>
			/// A mask containing not alive <see cref="InstanceStateKind" /> (i.e. NotAliveDisposedInstanceState and NotAliveNoWritersInstanceState)
			/// </summary>
			static const InstanceStateMask NotAliveInstanceState = ::DDS::NOT_ALIVE_INSTANCE_STATE;

		private:
			System::UInt32 m_value;

		internal:
			InstanceStateMask(System::UInt32 value);

		public:
			/// <summary>
			/// Implicit conversion operator from <see cref="InstanceStateMask" /> to <see cref="System::UInt32" />.
			/// </summary>
			/// <param name="value">The value to transform.</param>
			/// <returns>The <see cref="System::UInt32" /> value.</returns>
			static operator System::UInt32(InstanceStateMask value) {
				return value.m_value;
			}

			/// <summary>
			/// Implicit conversion operator from <see cref="System::UInt32" /> to <see cref="InstanceStateMask" />.
			/// </summary>
			/// <param name="value">The value to transform.</param>
			/// <returns>The <see cref="InstanceStateMask" /> value.</returns>
			static operator InstanceStateMask(System::UInt32 value) {
				InstanceStateMask r(value);
				return r;
			}

		};
	}
};
