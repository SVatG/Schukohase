#!/bin/sh
cd gfx_source
perl prepareimages.pl
cd ..
cp gfx_source/pal_merged/*.png gfx/
