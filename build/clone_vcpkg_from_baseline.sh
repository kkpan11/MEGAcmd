#!/bin/bash
set -e

#Currently libuv uses a git-tree older than baseline, enforcing older commit here:
VCPKG_OLDEST_COMMIT=293f090a9be5a88a2a77838c6346d5ef9d3df81b

if [ -z ${VCPKG_OLDEST_COMMIT+x} ]; then
    commit=$(grep '."builtin-baseline"' vcpkg.json  | awk -F '"' '{print $(NF-1)}')
else
    commit="${VCPKG_OLDEST_COMMIT}"
fi
commit_date=$(curl -s "https://api.github.com/repos/microsoft/vcpkg/commits/$commit" | grep '"date"' |  head -n 1 | awk -F '"' '{print $(NF-1)}')
git clone --shallow-since $commit_date https://github.com/microsoft/vcpkg $@
