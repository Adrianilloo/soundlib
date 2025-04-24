# Sound Info Library
SourceMod extension which is able to read various kinds of information out of WAV/MP3 files that have the ID3 tag besides of the sound length

## Building
Prepare a SM extensions environment, following these common [requirements](https://wiki.alliedmods.net/Building_SourceMod#Requirements).

Then, enter the following commands in the same directory:

```
mkdir build
cd build
```

Now, it's time to effectively compile the extension. If you're building for Windows, you need to open **Visual Studio 2022 Developer Command Prompt** to continue with the remaining steps.

For Windows, execute:

```
python ..\configure.py --hl2sdk-root=<HL2SDKs parent directory> --mms-path=<MM:S directory> --sm-path=<SM directory> -s present --enable-optimize --targets x86,x64
```

For Linux, type in a normal shell:

```
python ../configure.py --hl2sdk-root=<HL2SDKs parent directory> --mms-path=<MM:S directory> --sm-path=<SM directory> -s present --enable-optimize --targets x86,x64
```

(To force Clang, prepend `CC=clang CXX=clang++` to the above call).

Finally, just enter: `ambuild` (on any OS).

Output files should be created at `package` folder under active `build` directory, with the same hierarchy than classic `addons` server folder for SourceMod.

Not tried on Mac OS X.

## Notes on TagLib
This required library is already embed and was manually built with a low size, excluding support for unneeded audio file formats (leaving only MPEG and WAV). Also, a build is present for Windows and Linux with both 32/64 bit support.

As such, and, to serve as a reference, it was approximately configured as follows (skipping few target-specific flags):

```
cmake -E env CXXFLAGS="-fPIC" cmake -Bbuild -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_TESTING=0 -DENABLE_STATIC_RUNTIME=1 -DVISIBILITY_HIDDEN=1 -WITH_APE=0 -DWITH_ASF=0 -DWITH_DSF=0 -DWITH_MOD=0 -DWITH_MP4=0 -DWITH_SHORTEN=0 -DWITH_TRUEAUDIO=0 -DWITH_VORBIS=0 -DWITH_ZLIB=0
```
