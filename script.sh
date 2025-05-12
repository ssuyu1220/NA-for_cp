#!/bin/sh
export LDAPTLS_REQCERT=never
exec /usr/bin/ldapsearch -x -LLL -H ldaps://localhost \
  -b "ou=People,dc=35,dc=nasa" \
  "(&(objectClass=posixAccount)(uid=$1))" sshPublicKey 2>/dev/null | \
  sed -n '/^ /{H;d};/sshPublicKey:/x;$g;s/\n *//g;s/sshPublicKey: //gp'
