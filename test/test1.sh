wget https://www.gutenberg.org/cache/epub/10/pg10.txt -q
../bin/Encrypter pg10.txt output.bin > /dev/null
../bin/Decrypter output.bin decompressed.txt > /dev/null
if [[ $(diff decompressed.txt pg10.txt) ]]; then
  echo "Error in test1"
  exit 1
else
  echo "Success in test1!"
  exit 0
fi
