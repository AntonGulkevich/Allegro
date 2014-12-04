/*
    Copyright (c) 2011 - Tőkés Attila (tokes_atti@yahoo.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    See the LICENSE file for more details.
*/

#include "quotedprintable.h"
#include <iostream>
#include <QDebug>

QByteArray& QuotedPrintable::encode(const QByteArray &input)
{
    QByteArray *output = new QByteArray();

    char byte;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (int i = 0; i < input.length() ; ++i)
    {
        byte = input[i];

        if ((byte == 0x20) || (byte >= 33) && (byte <= 126) && (byte != 61))
        {
            output->append(byte);
        }
        else
        {
            output->append('=');
            output->append(hex[((byte >> 4) & 0x0F)]);
            output->append(hex[(byte & 0x0F)]);
        }
    }

    return *output;
}


QByteArray& QuotedPrintable::decode(const QByteArray &input)
{
    //                    0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B   C   D   E   F
    const int hexVal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};

    QByteArray *output = new QByteArray();

    for (int i = 0; i < input.length(); ++i)
    {
        if (input.at(i) == '=')
        {
            if((input.at(i+1)=='\r')&&(input.at(i+2)=='\n')){
                i+=2;
                continue;
            }
            output->append((hexVal[input.at(++i) - '0'] << 4) + hexVal[input.at(++i) - '0']);
        }
        else
        {
            output->append(input.at(i));
        }
    }

    return *output;
}
