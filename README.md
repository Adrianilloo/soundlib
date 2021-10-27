# Sound Info Library
SourceMod extension which is able to read various kinds of information out of WAV/MP3 files that have the ID3 tag besides of the sound length

## Building
Prepare a SM extensions environment, following these common [requirements](https://wiki.alliedmods.net/Building_SourceMod#Requirements).

Next, download [these](https://raw.githubusercontent.com/alliedmodders/sourcemod/master/public/sample_ext/configure.py) [files](https://raw.githubusercontent.com/alliedmodders/sourcemod/master/public/sample_ext/AMBuildScript) and place them in the project's root directory.

Then, enter the following commands in the same directory:

```
mkdir build
cd build
```

Now, it's time to effectively compile the extension. If you're building for Windows, you need to switch to the "VS2015 x86 Native Tools Command Prompt" to continue with the remaining steps.

For Windows, execute:

```
python ..\configure.py --hl2sdk-root=<HL2SDKs parent directory> --mms-path=<MM:S directory> --sm-path=<SM directory> --enable-optimize
```

For Linux (you'll need Clang), type in a normal shell:

```
CC=clang CXX=clang++ python ../configure.py --hl2sdk-root=<HL2SDKs parent directory> --mms-path=<MM:S directory> --sm-path=<SM directory> --enable-optimize
```

Finally, just enter: `ambuild` (on any OS).

(Not tried on Mac OS X)

Output files should be created at `package` folder under active `build` directory, with the same hierarchy than classic `addons` server folder for SourceMod.
