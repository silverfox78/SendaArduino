#!/bin/bash

origen="./libreria/TemporamaLib"
destino="/c/Users/sbarr/OneDrive/Documentos/Arduino/libraries/TemporamaLib"

rm -rf $destino

echo "Copiando archivos..."
cp -Rv $origen $destino

echo "Verificando archivos..."
if diff -rq $origen $destino; then
  echo "Todos los archivos fueron copiados correctamente."
else
  echo "Hubo un error al copiar los archivos."
fi