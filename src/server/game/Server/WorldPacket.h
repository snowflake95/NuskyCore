/*
 * Copyright (C) 2013-2018 NuskyCore <http://www.nuskycore.org/>
 * Copyright (C) 2008-2018 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2018 MaNGOS <https://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NuskySERVER_WORLDPACKET_H
#define NuskySERVER_WORLDPACKET_H

#include "Common.h"
#include "Opcodes.h"
#include "ByteBuffer.h"

struct z_stream_s;

class WorldPacket : public ByteBuffer
{
    public:
                                                            // just container for later use
        WorldPacket() : ByteBuffer(0), m_opcode(UNKNOWN_OPCODE), m_rcvdOpcodeNumber(0)
        {
        }

        WorldPacket(Opcodes opcode, size_t res = 200) : ByteBuffer(res), m_opcode(opcode), m_rcvdOpcodeNumber(0)
        {
        }
                                                            // copy constructor
        WorldPacket(WorldPacket const& packet) : ByteBuffer(packet), m_opcode(packet.m_opcode), m_rcvdOpcodeNumber(0)
        {
        }

        void Initialize(Opcodes opcode, size_t newres = 200)
        {
            clear();
            _storage.reserve(newres);
            m_opcode = opcode;
        }

        Opcodes GetOpcode() const { return m_opcode; }
        void SetOpcode(Opcodes opcode) { m_opcode = opcode; }
        void Compress(z_stream_s* compressionStream);
        void Compress(z_stream_s* compressionStream, WorldPacket const* source);
        void SetReceivedOpcode(uint16 opcode) { m_rcvdOpcodeNumber = opcode; }
        uint16 GetReceivedOpcode() { return m_rcvdOpcodeNumber; }

    protected:
        Opcodes m_opcode;
        uint16 m_rcvdOpcodeNumber;
        void Compress(void* dst, uint32 *dst_size, const void* src, int src_size);
        z_stream_s* _compressionStream;
};
#endif