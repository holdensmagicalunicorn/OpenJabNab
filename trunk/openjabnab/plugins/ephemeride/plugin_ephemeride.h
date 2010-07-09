#ifndef _PLUGINEPHEMERIDE_H_
#define _PLUGINEPHEMERIDE_H_

#include <QHttp>
#include <QMultiMap>
#include <QTextStream>
#include <QThread>
#include "plugininterface.h"
	
class PluginEphemeride : public PluginInterface
{
	friend class PluginEphemeride_Worker;
	Q_OBJECT
	Q_INTERFACES(PluginInterface)
	
private slots:
	void analyseXml();
	void analyseDone(bool, Bunny*, QByteArray);

public:
	PluginEphemeride();
	virtual ~PluginEphemeride();
	virtual bool Init();
	
	bool OnClick(Bunny *, PluginInterface::ClickType);
	void OnCron(QVariant);
	void OnBunnyConnect(Bunny *);
	void OnBunnyDisconnect(Bunny *);

	// API
	void InitApiCalls();
	PLUGIN_BUNNY_API_CALL(Api_AddWebcast);
	PLUGIN_BUNNY_API_CALL(Api_RemoveWebcast);

private:
	void getEphemeridePage(Bunny *);
	QMultiMap<Bunny*, QPair<int, QString> > webcastList;
	QDir ephemerideFolder;

};

class PluginEphemeride_Worker : public QThread
{
	Q_OBJECT

signals:
	void done(bool, Bunny*, QByteArray);

public:
	PluginEphemeride_Worker(PluginEphemeride * , Bunny *, QByteArray);
	virtual ~PluginEphemeride_Worker() {}
	void run();

private:
	PluginEphemeride * plugin;
	Bunny * bunny;
	QByteArray buffer;

};

#endif
