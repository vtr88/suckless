#!/bin/sh

set -eu

uri=${1:-about:blank}
scriptdir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

if [ -x "$scriptdir/surf-session" ]; then
	session=$scriptdir/surf-session
else
	session=surf-session
fi

"$session" "$uri"
