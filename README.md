# wbr

White Background Remover - Removes white backgrounds from images, creating transparent PNGs.

<p align="center">
  <img src="media/moon.jpg" width="300" alt="Before" style="vertical-align: middle;" />
  <span style="font-size: 4em; margin: 0 20px; vertical-align: middle;">→</span>
  <img src="media/moon_nobg.png" width="300" alt="After" style="vertical-align: middle;" />
</p>
<p align="center">
  <em>Before</em>
  <span style="margin: 0 180px;"></span>
  <em>After</em>
</p>

## Build

```bash
mkdir build && cd build
cmake .. && make
```

## Usage

```bash
./wbr <input_image>
```

Creates `<input>_nobg.png` with transparent background.
