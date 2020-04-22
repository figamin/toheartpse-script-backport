# ToHeart utils

To use:

```
cd LVNS3
make extract decompile compile

mkdir indir outdir
cd indir
../extract ../LVNS3SCN.PAK

for file in *.DATA *.TEXT; do
  ../decompile ${file} ../outdir/${file}
done

# modify the decompiled scripts in `outdir/`

cd ../outdir/
for file in *.DATA *.TEXT; do
  ../compile ${file} ../indir/${file}
done
```
