#include "sound-duration.h"
#include "SoundFile.h"
#include <filesystem.h>

#define SIZEOFARRAY(ARRAY) sizeof(ARRAY) / sizeof(ARRAY[0])

SoundLibrary g_SoundLibrary;
CListener g_CListener;
IGameConfig* gameconfigs = NULL;
IFileSystem* filesystem = NULL;
extern sp_nativeinfo_t g_SoundLibraryNatives[];

SMEXT_LINK(&g_SoundLibrary);

class FileTypeHandler : public IHandleTypeDispatch
{
public:
	void OnHandleDestroy(HandleType_t type, void* object)
	{
		delete (SoundFile*)object;
	}
};

/* Create an instance of the handler */
FileTypeHandler g_FileTypeHandler;


static cell_t OpenSoundFile(IPluginContext* pContext, const cell_t* params) {
	char* path;
	int err, type = SOUNDTYPE_WAVE, basePathLen = 0;

	if ((err = pContext->LocalToString(params[1], &path)) != SP_ERROR_NONE) {
		pContext->ThrowNativeErrorEx(err, NULL);
		return 0;
	}

	if (strlen(path) > (PLATFORM_MAX_PATH - 7)) {
		pContext->ThrowNativeError("Specified Path too long");
		return 0;
	}

	char* file_extension = strrchr(path, '.'), realpath[PLATFORM_MAX_PATH];

	if (file_extension == NULL) {
		return 0;
	}
	else if (strcmp(file_extension, ".mp3") == 0) {
		type = SOUNDTYPE_MP3;
	}
	else if (strcmp(file_extension, ".wav") != 0) {
		return 0;
	}

	if (params[2]) {
		basePathLen = g_pSM->BuildPath(Path_Game, realpath, sizeof(realpath), "");
		snprintf(realpath + basePathLen, sizeof(realpath) - basePathLen, "sound/%s", path);
		path = realpath;
	}

	CUtlBuffer buffer;
	SoundFile* soundfile = new SoundFile(path, type);

	if (!soundfile->isOpen()) {
		// Try with HL2 filesystem instead (file might be in a VPK)
		if (filesystem->ReadFile(path + basePathLen, NULL, buffer))
		{
			delete soundfile;
			soundfile = new SoundFile(buffer, type);
		}

		if (!soundfile->isOpen()) {
			delete soundfile;
			return 0;
		}
	}

	soundfile->loadTag();
	return g_pHandleSys->CreateHandle(g_SoundFileType, soundfile, pContext->GetIdentity(), myself->GetIdentity(), NULL);
}

static cell_t GetSoundLength(IPluginContext* pContext, const cell_t* params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	return soundfile->getSoundDuration();
}

static cell_t GetSoundLengthFloat(IPluginContext* pContext, const cell_t* params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	return sp_ftoc(soundfile->getSoundDurationFloat());
}

static cell_t GetSoundBitRate(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	return soundfile->getSoundBitRate();
}

static cell_t GetSoundSamplingRate(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	return soundfile->getSoundSamplingRate();
}

static cell_t GetSoundArtist(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	char str[128];
	soundfile->getSoundArtist(str, SIZEOFARRAY(str));

	return pContext->StringToLocalUTF8(params[2], static_cast<size_t>(params[3]), str, NULL);
}

static cell_t GetSoundTitle(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	char str[128];
	soundfile->getSoundTitle(str, SIZEOFARRAY(str));

	return pContext->StringToLocalUTF8(params[2], static_cast<size_t>(params[3]), str, NULL);
}

static cell_t GetSoundNum(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	return soundfile->getSoundNum();
}

static cell_t GetSoundAlbum(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	char str[128];
	soundfile->getSoundAlbum(str, SIZEOFARRAY(str));

	return pContext->StringToLocalUTF8(params[2], static_cast<size_t>(params[3]), str, NULL);
}

static cell_t GetSoundYear(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	return  soundfile->getSoundYear();


}

static cell_t GetSoundComment(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	char str[1024];
	soundfile->getSoundComment(str, SIZEOFARRAY(str));

	return pContext->StringToLocalUTF8(params[2], static_cast<size_t>(params[3]), str, NULL);
}

static cell_t GetSoundGenre(IPluginContext* pContext, const cell_t* params) {
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	HandleError err;
	HandleSecurity sec;

	/* Build our security descriptor */
	sec.pOwner = NULL;	/* Not needed, owner access is not checked */
	sec.pIdentity = myself->GetIdentity();	/* But only this extension can read */

	SoundFile* soundfile;
	if ((err = g_pHandleSys->ReadHandle(hndl, g_SoundFileType, &sec, (void**)&soundfile))
		!= HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid sound-file handle %x (error %d)", hndl, err);
	}

	char str[1024];
	soundfile->getSoundGenre(str, SIZEOFARRAY(str));

	return pContext->StringToLocalUTF8(params[2], static_cast<size_t>(params[3]), str, NULL);
}

bool SoundLibrary::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late) {
	GET_V_IFACE_CURRENT(GetEngineFactory, filesystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
	return true;
}

void SoundLibrary::SDK_OnAllLoaded() {

	return;
}

bool SoundLibrary::SDK_OnLoad(char* error, size_t maxlength, bool late) {
	g_SoundFileType = g_pHandleSys->CreateType("SoundFile", &g_FileTypeHandler, 0, NULL, NULL, myself->GetIdentity(), NULL);

	sharesys->AddNatives(myself, g_SoundLibraryNatives);

	return true;
}

void SoundLibrary::SDK_OnUnload() {
	g_pHandleSys->RemoveType(g_SoundFileType, myself->GetIdentity());
}

bool SoundLibrary::QueryRunning(char* error, size_t maxlength) {
	return true;
}


void CListener::OnClientPutInServer(int client) {

}

void CListener::OnClientDisconnecting(int client) {

}

sp_nativeinfo_t g_SoundLibraryNatives[] =
{
	{"OpenSoundFile",			OpenSoundFile},
	{"GetSoundLength",			GetSoundLength},
	{"GetSoundLengthFloat",		GetSoundLengthFloat},
	{"GetSoundBitRate",			GetSoundBitRate},
	{"GetSoundSamplingRate",	GetSoundSamplingRate},
	{"GetSoundArtist",			GetSoundArtist},
	{"GetSoundTitle",			GetSoundTitle},
	{"GetSoundNum",				GetSoundNum},
	{"GetSoundAlbum",			GetSoundAlbum},
	{"GetSoundYear",			GetSoundYear},
	{"GetSoundComment",			GetSoundComment},
	{"GetSoundGenre",			GetSoundGenre},
	{NULL,						NULL},
};
