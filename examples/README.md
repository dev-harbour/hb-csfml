# Getting started

- [Harbour programming language](https://en.wikipedia.org/wiki/Harbour_(programming_language))
- [Homepage](https://harbour.github.io)
- Select your Harbour:
   - https://sourceforge.net/projects/harbour-project/files/
   - https://github.com/harbour/core
   - https://github.com/vszakats/harbour-core

## Installing on Windows

Downloading SFML Distributions for Windows.

- https://github.com/SFML/CSFML/releases/tag/2.5.1

Unpack in the directory:

```
c:\SFML\bin *.dll
c:\SFML\include *.h
c:\SFML\lib *.a
```

## Installing on Linux

```
sudo apt-get update
sudo apt-get install libcsfml-dev libcsfml-doc
```

## Installing on Mac OSX

Downloading SFML Distributions (Mac OSX)

- [Mac OSX 10.x, Intel](https://github.com/SFML/CSFML/releases/tag/2.5.1)

## Install hb-SFML

- [Downloading hb-sfml](https://github.com/rjopek/hb-sfml/archive/refs/heads/main.zip)

Environment Variables

- Windows

   ```
   set HB_WITH_CSFML=c:\SFML\include
   set PATH=c:\SFML\bin;%path%
   ```

- Linux

   ```
   export HB_WITH_CSFML=/usr/include
   ```

- Build static library:

   ```
   hbmk2 hbsfml.hbp
   ```

- Build and run sample and test code:

   ```
   cd cd examples/harbour
   hbmk2 example_00.prg
   ./example_00
   ```

[Edit me](https://github.com/rjopek/hb-sfml/edit/main/examples/README.md)
