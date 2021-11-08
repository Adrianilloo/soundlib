
// enforce semicolons after each code statement
#pragma semicolon 1

#include <sourcemod>
#include <soundlib>

#define VERSION "1.0"



/*****************************************************************


			P L U G I N   I N F O


*****************************************************************/

public Plugin:myinfo = {
	name = "soundlib test",
	author = "Berni",
	description = "Plugin by Berni",
	version = VERSION,
	url = "http://forums.alliedmods.net"
}



/*****************************************************************


			G L O B A L   V A R S


*****************************************************************/





/*****************************************************************


			F O R W A R D   P U B L I C S


*****************************************************************/

public OnPluginStart() {
	RegAdminCmd("sm_soundinfo", Command_SoundInfo, ADMFLAG_GENERIC);
}



/****************************************************************


			C A L L B A C K   F U N C T I O N S


****************************************************************/

public Action:Command_SoundInfo(client, args) {

	decl String:path[PLATFORM_MAX_PATH];
	
	GetCmdArgString(path, sizeof(path));

	SoundFile soundFile = new SoundFile(path);
	
	if (soundFile == null) {
		PrintToServer("Invalid handle!");
		return Plugin_Handled;
	}
	
	decl String:artist[64];
	decl String:title[64];
	decl String:album[64];
	decl String:comment[64];
	decl String:genre[64];
	
	soundFile.GetArtist(artist, sizeof(artist));
	soundFile.GetTitle(title, sizeof(title));
	soundFile.GetAlbum(album, sizeof(album));
	soundFile.GetComment(comment, sizeof(comment));
	soundFile.GetGenre(genre, sizeof(genre));
	
	ReplyToCommand(client, "Song Info %s", path);
	ReplyToCommand(client, "Sound Length: %d", soundFile.Length);
	ReplyToCommand(client, "Sound Length (float): %f", soundFile.LengthFloat);
	ReplyToCommand(client, "Birate: %d", soundFile.BitRate);
	ReplyToCommand(client, "Sampling Rate: %d", soundFile.SamplingRate);
	ReplyToCommand(client, "Artist: %s", artist);
	ReplyToCommand(client, "Title: %s", title);
	ReplyToCommand(client, "Num %d", soundFile.Number);
	ReplyToCommand(client, "Album: %s", album);
	ReplyToCommand(client, "Year: %d", soundFile.Year);
	ReplyToCommand(client, "Comment: %s", comment);
	ReplyToCommand(client, "Genre: %s", genre);
	
	delete soundFile;
	return Plugin_Handled;
}



/*****************************************************************


			P L U G I N   F U N C T I O N S


*****************************************************************/

