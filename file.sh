% (tr ' ' '\n' | sort | uniq -c | awk '{print $2"@"$1}') <<EOF

mayusculas a minusculas
tr 'A-Z' 'a-z' < quijote.txt > hola
