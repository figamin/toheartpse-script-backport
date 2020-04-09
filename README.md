# ToHeart utils

To use:

```
make extract decompile compile

mkdir indir outdir
cd indir
../extract ../LVNS3SCN.PAK

for file in *.DATA *.TEXT; do
  ../decompile ${file} ../outdir/${file}
done

# modify the decompiled scripts in `outdir/`

cd ../indir/
for file in *.DATA *.TEXT; do
  ../compile ${file} ../indir/${file}
done
```
