![LOGO](/images/banner.png)

# Texel-BodyScan-Dataset
A dataset of 3D human body scans for non-commercial research, collected by TEXEL LLC and Lomonosov Moscow State University.
If you need more, consider [commercial edition](https://texel.graphics/texel-3d-body-model-dataset/)
with thousands of these body scans.

## Possible use cases

* 3D human scans to enrich other datasets (take a look at [THUman2.1](https://github.com/ytrock/THuman2.0-Dataset))
* Additional RGB-D recordings for tuning your full body scanning algorithm
* Data to train your ML models (photo to 3D mesh, photo to body measurements, etc)

## Structure

The presented scans were collected during various events under various conditions. Some persons were consent to make their
scans publicly available, while others choose to share only the depth maps. To structure the dataset, we divided it into a
few parts with the following characteristics:

|       | Number <br>of persons | Of which <br>men | Of which <br>women | Scans <br>per person   | Clothing type          | Total size |
| ----- | :-------------------: | :--------------: | :----------------: | :--------------------: | :--------------------: | :--------: |
| Part1 | 10                    | 5                | 5                  | 1                      | Underwear              | 200 MB     |
| Part2 | 42                    | 3                | 39                 | 5                      | Underwear, <br/>tight  | 1.16 GB    |

Depending on the part number, the 'scan' word has a slightly different meaning. In general, it may consist of a 3D body
mesh, a SMPL/STAR parametric model fitted to it, automatic body measurements and original RGB-D frames obtained from the
depth sensor:

|       | Depth maps | Color frames | Measurements                   | Portal MX                | Free Fusion              |
| ----- | :--------: | :----------: | :----------------------------: | :----------------------: | :----------------------: |
| Part1 | Yes        | No           | ISO 8559-1                     | 3D scan + SMPL           | 3D scan + SMPL           |
| Part2 | Yes        | No           | ISO 8559-1 <br>(will be added) | SMPL <br>(will be added) | SMPL <br>(will be added) |

You can expect the files to be organized in the scan directory as follows:
```
/PartN/
│   ├── PersonK/
│   │   ├── frames/                     # Depth maps (.png, 16-bit, grayscale) 
│   │   ├── color/                      # RGB frames (.jpg)
│   │   ├── portal_mx/
│   │   |   ├── scan.ply                # 3D mesh of the person scanned by Portal MX
│   │   |   ├── model_smpl300.json      # Shape and pose parameters for SMPL300
|   |   |   |                             (SMPL10 and STAR300 can also be met)
│   │   |   ├── model_smpl300.ply       # 3D mesh for SMPL300
│   │   |   └── measurements.csv        # Automatic body measurements
|   |   |                                 (ISO 8559-1, some values may be omitted)
│   │   ├── free_fusion/
│   │   |   ├── scan.ply                # The same for FreeFusion
│   │   |   ├── model_smpl300.json      # The same for FreeFusion
│   │   |   ├── model_smpl300.ply       # The same for FreeFusion
│   │   |   └── measurements.csv        # The same for FreeFusion
│   │   ├── person.scan.xml             # Full metadata
|   |   |                                 (camera intrinsics, gender, age, clothing, etc)
│   │   └── person.json                 # Only camera intrinsics and bounding box
```

## Scanners

We consider [TEXEL Portal MX](https://texel.graphics/3d-scanners/portal-mx/), a high-resoultion scanner from TEXEL LLC,
as the baseline. It is capable of creating colored 3D meshes, fitting SMPL300 to them and performing body measurements
in accordance with ISO 8559-1. However, the MX scanner family has received a series of hardware and software upgrades
(new IR sensors, new platform, AI-based post-processing, etc). So, the accuracy of the presented scans may vary depending
on the date they were recorded. If you need information about the actual models, please contact [TEXEL support](https://texel.graphics/contacts/).

![Portal MX](/images/portal_mx.png)

In opposite to it, Free Fusion is just an algorithm developed by TEXEL LLC in cooperation with Lomonosov Moscow State
University. It produces the same data (3D mesh, fitted SMPL, body measurements) using only one RGB-D ToF sensor. In
addition, the person being scanned can move freely, which greatly simplifies the scanning process. On the other hand,
these scans have coarse detail and introduce additional errors into the measurements.

![Free Fusion](/images/free_fusion.png)

Depth maps and color frames are the original recordings from Azure Kinect, used by Free Fusion (not Portal MX!) to
reconstruct 3D meshes. The only fix was made is distortion mitigation using OpenCV.

## Preview

Free Fusion enriches the scan surface with synthetic frames from the fitted parametric model (more details in our paper),
so the overall quality is very plausible. But please bear in mind that it is a non-rigid approach for fusing depth maps from
a single sensor. Therefore, outliers, failed scans and distorted body proportions are our frequent guests. Especially, if a
person was not wearing tight clothing.

![Scan preview](/images/preview.png)

## Utilities

Files with the `*.scan.xml` extension contain information about depth maps, color frames and annotations for a single RGB-D
recording. Our `IterateScans` utility allows you to traverse some directory and print all available information about this
raw data, which is sufficient for reconstructing a 3D scan using Free Fusion. To compile `IterateScans` in your home directory,
you could use `git`, `cmake`, `make` and `g++` like this:

```bash
git clone https://github.com/m-krivov/Texel-BodyScan-Dataset.git ~/texel_bodyscan_dataset
cd ~/texel_bodyscan_dataset
git submodule init
git submodule update
cmake -S ./ -B ./build
make -C ./build
./bin/IterateScans <directory_with_scans>
```

Currently, `IterateScans` ignores presence of 3D meshes and body measurements, but we plan to fix it in future updates. The
output might look like the follows. Feel free to adapt this utility to your needs.

```
./bin/IterateScans Samples

'Samples_Fedyukov_Maxim':
  Maxim Fedyukov (male): adult person
  Appearance: short haircut, almost naked, barefoot or in socks
  Free Fusion (Azure Kinect DK): depth 960x864 (369 frames), no color frames, indoor


'Samples_Krivov_Maxim':
  Maxim Krivov (male): adult person, 35 years old, 178 cm, 58 kg
  Appearance: short haircut, outerwear, flat boots
  Free Fusion (Azure Kinect DK): depth 960x864 (229 frames), color 2048x1536 (230 frames), indoor

Found information about 2 scans (2 men, 0 women)
```

## Direct links
To get our dataset, you can use the following links: [Part1](https://disk.yandex.ru/d/5R57d5509rP7jQ) (140 MB),
[Part2](https://disk.yandex.ru/d/aXTJ1eoJYbJngA) (935 MB). Since we are going to append new scans from time to time,
these direct links may become invalid. If this happens, visit our repo for the new ones.

## License
- **Dataset (depth maps, scans, annotations)**: [CC-BY-NC 4.0](LICENSE-DATA)
  (Free for non-commercial research; commercial use requires separate agreement).
- **Code (C++ parser)**: [MIT License](LICENSE-CODE)
  (Use freely, even commercially).
