#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_


#include "smsdk_ext.h"


class SoundLibrary : public SDKExtension
{
public:
	/**
	 * @brief This is called after the initial loading sequence has been processed.
	 *
	 * @param error		Error message buffer.
	 * @param maxlength	Size of error message buffer.
	 * @param late		Whether or not the module was loaded after map load.
	 * @return			True to succeed loading, false to fail.
	 */
	virtual bool SDK_OnLoad(char* error, size_t maxlength, bool late);

	/**
	 * @brief This is called right before the extension is unloaded.
	 */
	virtual void SDK_OnUnload();

	/**
	 * @brief This is called once all known extensions have been loaded.
	 * Note: It is is a good idea to add natives here, if any are provided.
	 */
	virtual void SDK_OnAllLoaded();

	/**
	 * @brief Called when the pause state is changed.
	 */
	 //virtual void SDK_OnPauseChange(bool paused);

	 /**
	  * @brief this is called when Core wants to know if your extension is working.
	  *
	  * @param error		Error message buffer.
	  * @param maxlength	Size of error message buffer.
	  * @return			True if working, false otherwise.
	  */
	virtual bool QueryRunning(char* error, size_t maxlength);

	void Hook_ImpulseCommands();
	bool ImpulseCommands(int client, int impulse);

	/**
	 * @brief Called when Metamod is attached, before the extension version is called.
	 *
	 * @param error			Error buffer.
	 * @param maxlength		Maximum size of error buffer.
	 * @param late			Whether or not Metamod considers this a late load.
	 * @return				True to succeed, false to fail.
	 */
	virtual bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlength, bool late);
};

class CListener : public IClientListener
{
public:
	void OnClientPutInServer(int client);
	void OnClientDisconnecting(int client);
};

#endif // _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
