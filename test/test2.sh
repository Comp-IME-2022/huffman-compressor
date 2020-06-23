wget http://www.africau.edu/images/default/sample.pdf -q
../bin/Encrypter sample.pdf output.bin > /dev/null
../bin/Decrypter output.bin decompressed.txt > /dev/null
if [[ $(diff decompressed.txt sample.pdf) ]]; then
  echo "Error in test2"
  exit 1
else
  echo "Success in test2!"
  exit 0
fi
