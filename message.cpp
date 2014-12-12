#include "message.h"

Message::Message()
    :from(),
     fromMes(),
     to(),
     head(),
     date(),
     messagePartList(),
     transferEncodingPartList(),
     textEncodingPartList(),
     contentTypePartList(),
     contentSubtypePartList(),
     uidl(),
     number(0)
{}



Message::Message(const Message &original)
    :from(original.from),
     fromMes(original.fromMes),
     to(original.to),
     head(original.head),
     date(original.date),
     messagePartList(original.messagePartList),
     transferEncodingPartList(original.transferEncodingPartList),
     textEncodingPartList(original.textEncodingPartList),
     contentTypePartList(original.contentTypePartList),
     contentSubtypePartList(original.contentSubtypePartList),
     uidl(original.uidl),
     number(original.number)
{}

Message::~Message(){
}
