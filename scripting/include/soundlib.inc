#if defined _soundlib_included
	#endinput
#endif
#define _soundlib_included

/**
 * Do not edit below this line!
 */
public Extension:__ext_soundlib = 
{
	name = "Sound Info Library",
	file = "soundlib.ext",

#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif

#if defined REQUIRE_EXTENSIONS
	required = 1
#else
	required = 0
#endif
};

/**
* Opens a sound file.
*
* @note Sound files are closed with CloseHandle().
*
* @param file                File to open
* @param relativeToSound     If true, it is relative to the sound directory, otherwise you have to build the path yourself
* @return                    A Handle to the sound file, INVALID_HANDLE on open error.
*/
native Handle:OpenSoundFile(const String:file[], bool:relativeToSound = true);

/**
* Gets the length of the sound file in seconds
*
* @param hndl                Handle to the sound file
* @return                    The song length in seconds
*/
native GetSoundLength(Handle:hndl);

/**
* Gets the length of the sound file in seconds as float.
* Note: this probably won't work with some VBR encoded mp3's
*
* @param hndl                Handle to the sound file
* @return                    The song length in seconds as float
*/
native Float:GetSoundLengthFloat(Handle:hndl);

/**
* Get the Bit rate of sound (kbps)
*
* @param hndl                Handle to the sound file
* @return                    Sound bitrate (cell)
*/
native GetSoundBitRate(Handle:hndl);

/**
* Get the Sampling rate of sound (hz)
*
* @param hndl                Handle to the sound file
* @return                    Sampling rate (cell)
*/
native GetSoundSamplingRate(Handle:hndl);

/**
* Get the Artist of the sound
*
* @param hndl                Handle to the sound file
* @param buffer              Buffer to use for storing the string.
* @param maxlength           Maximum length of the buffer.
* @return                    Length of string written to buffer.
*/
native GetSoundArtist(Handle:hndl, String:buffer[], maxlength);

/**
* Get the Track title of sound
*
* @param hndl                Handle to the sound file
* @param buffer              Buffer to use for storing the string.
* @param maxlength           Maximum length of the buffer.
* @return                    Length of string written to buffer.
*/
native GetSoundTitle(Handle:hndl, String:buffer[], maxlength);

/**
* Get the Track number of the sound
*
* @param hndl                Handle to the sound file
* @return                    Sound number (cell)
*/
native GetSoundNum(Handle:hndl);

/**
* Get the Album of the sound
*
* @param hndl                Handle to the sound file
* @param buffer              Buffer to use for storing the string.
* @param maxlength           Maximum length of the buffer.
* @return                    Length of string written to buffer.
*/
native GetSoundAlbum(Handle:hndl, String:buffer[], maxlength);

/**
* Get the Year of sound
*
* @param hndl                Handle to the sound file
* @return                    Sound year (cell)
*/
native GetSoundYear(Handle:hndl);

/**
* Get the Comment of the sound
*
* @param hndl                Handle to the sound file
* @param buffer              Buffer to use for storing the string.
* @param maxlength           Maximum length of the buffer.
* @return                    Length of string written to buffer.
*/
native GetSoundComment(Handle:hndl, String:buffer[], maxlength);

/**
* Get the Genre of the sound
*
* @param hndl                Handle to the sound file
* @param buffer              Buffer to use for storing the string.
* @param maxlength           Maximum length of the buffer.
* @return                    Length of string written to buffer.
*/
native GetSoundGenre(Handle:hndl, String:buffer[], maxlength);

#if (SOURCEMOD_V_MINOR >= 7)
methodmap SoundFile < Handle
{
	/**
	* Opens a sound file.
	*
	* @note Sound files are closed with CloseHandle().
	*
	* @param file                File to open
	* @param relativeToSound     If true, it is relative to the sound directory, otherwise you have to build the path yourself
	* @return                    A Handle to the sound file, null on open error.
	*/
	public native SoundFile(const char[] file, bool relativeToSound = true);

	/**
	* Gets the length of the sound file in seconds
	*
	* @return                    The song length in seconds
	*/
	property int Length
	{
		public native get();
	}

	/**
	* Gets the length of the sound file in seconds as float.
	* Note: this probably won't work with some VBR encoded mp3's
	*
	* @return                    The song length in seconds as float
	*/
	property float LengthFloat
	{
		public native get();
	}

	/**
	* Get the Bit rate of sound (kbps)
	*
	* @return                    Sound bitrate (cell)
	*/
	property int BitRate
	{
		public native get();
	}

	/**
	* Get the Sampling rate of sound (hz)
	*
	* @return                    Sampling rate (cell)
	*/
	property int SamplingRate
	{
		public native get();
	}

	/**
	* Get the Artist of the sound
	*
	* @param buffer              Buffer to use for storing the string.
	* @param maxlength           Maximum length of the buffer.
	* @return                    Length of string written to buffer.
	*/
	public native int GetArtist(char[] buffer, int maxlength);

	/**
	* Get the Track title of sound
	*
	* @param buffer              Buffer to use for storing the string.
	* @param maxlength           Maximum length of the buffer.
	* @return                    Length of string written to buffer.
	*/
	public native int GetTitle(char[] buffer, int maxlength);

	/**
	* Get the Track number of the sound
	*
	* @return                    Sound number (cell)
	*/
	property int Number
	{
		public native get();
	}

	/**
	* Get the Album of the sound
	*
	* @param buffer              Buffer to use for storing the string.
	* @param maxlength           Maximum length of the buffer.
	* @return                    Length of string written to buffer.
	*/
	public native int GetAlbum(char[] buffer, int maxlength);

	/**
	* Get the Year of sound
	*
	* @return                    Sound year (cell)
	*/
	property int Year
	{
		public native get();
	}

	/**
	* Get the Comment of the sound
	*
	* @param buffer              Buffer to use for storing the string.
	* @param maxlength           Maximum length of the buffer.
	* @return                    Length of string written to buffer.
	*/
	public native int GetComment(char[] buffer, int maxlength);

	/**
	* Get the Genre of the sound
	*
	* @param buffer              Buffer to use for storing the string.
	* @param maxlength           Maximum length of the buffer.
	* @return                    Length of string written to buffer.
	*/
	public native int GetGenre(char[] buffer, int maxlength);
};
#endif // (SOURCEMOD_V_MINOR >= 7)
