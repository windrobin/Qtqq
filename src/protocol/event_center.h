#ifndef EVENT_CENTER_H
#define EVENT_CENTER_H

#include <QObject>
#include <QByteArray>
#include <QString>

#include "protocol/event.h"

namespace Protocol
{
    class EventCenter;
}

class Protocol::EventCenter : public QObject
{
    Q_OBJECT
signals:
    void eventTrigger(Protocol::Event *event);

public:
    static EventCenter *instance()
    {
        if ( !instance_ )
            instance_ = new EventCenter();

        return instance_;
    }

    Event *createGroupMemberListUpdateEvent(Group *group, QByteArray data)
    {
        return new GroupMemberListUpdateEvent(group, data);
    }
    Event *createAvatarUpdateEvent(Talkable *event_for, QByteArray data)
    {
        return new AvatarUpdateEvent(event_for, data);
    }
    Event *createMsgSendDoneEvent(Talkable *sender, QByteArray data)
    {
        return new MsgSendDoneEvent(sender, data);
    }
    Event *createImgSendDoneEvent(Talkable *sender, bool is_sucess, QString file_path, QString img_id)
    {
        return new ImgSendDoneEvent(sender, is_sucess, file_path, img_id);
    }

    void triggerEvent(Event *event);

private:
    EventCenter(){}
    EventCenter(const EventCenter &);
    EventCenter &operator=(const EventCenter &);

    static EventCenter *instance_;
};

#endif //EVENT_CENTER_H