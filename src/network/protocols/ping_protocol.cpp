//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2013 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "network/protocols/ping_protocol.hpp"

#include "network/network_manager.hpp"
#include "utils/time.hpp"

PingProtocol::PingProtocol(const TransportAddress& ping_dst, double delay_between_pings) : Protocol(NULL, PROTOCOL_SILENT)
{
    m_ping_dst = ping_dst;
    m_delay_between_pings = delay_between_pings;
}

PingProtocol::~PingProtocol()
{
}

void PingProtocol::setup()
{
    m_last_ping_time = 0;
}

void PingProtocol::asynchronousUpdate()
{
    if (StkTime::getRealTime() > m_last_ping_time+m_delay_between_pings)
    {
        m_last_ping_time = StkTime::getRealTime();
        uint8_t data = 0;
        NetworkManager::getInstance()->getHost()->sendRawPacket(&data, 1, m_ping_dst);
        Log::info("PingProtocol", "Ping message sent");
    }
}
