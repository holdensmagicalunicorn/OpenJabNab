#ifndef _XMPPHANDLER_H_
#define _XMPPHANDLER_H_

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QByteArray>
#include "global.h"
#include "packet.h"

class Bunny;
class PluginManager;
class OJN_EXPORT XmppHandler : public QObject
{
	Q_OBJECT
	
public:
	XmppHandler(QTcpSocket *, PluginManager * p);
	void WritePacketToBunny(Packet const& p);

protected:
	virtual ~XmppHandler() {};

private slots:
	void HandleBunnyXmppMessage();
	void HandleVioletXmppMessage();
	void Disconnect();

private:
	QList<QByteArray> XmlParse(QByteArray const&);
	void WriteToBunny(QByteArray const&);

	QTcpSocket * incomingXmppSocket;
	QTcpSocket outgoingXmppSocket;
	PluginManager * pluginManager;
	Bunny * bunny;
	QByteArray msgQueue;
	
	static unsigned short msgNb;
};

#endif