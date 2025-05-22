![LOGO](https://downloader.disk.yandex.ru/disk/8707c4793d2ca96d3ebb1d56b153dadf7b00bd7ca6018428b38ec8c875015ce9/682cdcdc/fKqInKw3d7bLFOeFnMGnhNu1lH1fCxoqUMmmvAYBWwskYp0WxpgQceQJXPDcpTOAmNM-fNKohGxDqPAcQ_fsVBtrfa8dXu5Cdd85ZbLDqoqr8npumZHI4midPdWhecNq?uid=0&filename=banner.png&disposition=attachment&hash=uJHtLgPRVpznwVrLVDKp9XPXXal%2BbAXqbP%2BaeljPEUOWEIEwmn97q0SdDzETy6QUDqZvSgIch5AN9ddz7ydViQ%3D%3D%3A&limit=0&content_type=image%2Fpng&owner_uid=1130000067001764&fsize=23348&hid=0560440144e485bf7df0768d0ff467bd&media_type=image&tknv=v3)

# Texel-BodyScan-Dataset
A dataset of 3D human body scans for non-commercial research, collected by TEXEL LLC and Lomonosov Moscow State University.
If you need more, consider [commercial edition](https://texel.graphics/texel-3d-body-model-dataset/)
with thousands of these body scans.

## Possible use cases

* 3D human scans to enrich other datasets (take a look at [THUman2.1](https://github.com/ytrock/THuman2.0-Dataset))
* Additional RGB-D frames for tuning your full body scanning algorithm
* Data to train your ML models (photo to 3D mesh, photo to body measurements, etc)

## Structure

The presented scans were collected during various events under various conditions. Some persons were consent to make their
scans publicly available, while others choose to share only the depth maps. To structure the dataset, we divided it into a
few parts with the following characteristics:

|       | Number <br>of persons | Of which <br>men | Of which <br>women | Scans <br>per person   | Color <br>information | Total size |
| ----- | :-------------------: | :--------------: | :----------------: | :--------------------: | :-------------------: | :--------: |
| Part1 | 10                    | 5                | 5                  | 1                      | no                    | 200 MB     |
| Part2 | 42                    | 3                | 39                 | 5                      | no                    | 1.16 GB    |

Depending on the part number, the 'scan' word has a slightly different meaning. In general, it may consist of a 3D body
mesh, a SMPL/STAR parametric model fitted to it, automatic body measurements and original RGB-D frames obtained from the
depth sensor:

|       | Depth maps | Color frames | Measurements                   | Portal MX                | Free Fusion              |
| ----- | :--------: | :----------: | :----------------------------: | :----------------------: | :----------------------: |
| Part1 | yes        | no           | ISO 8559-1                     | 3D scan + SMPL           | 3D scan + SMPL           |
| Part2 | yes        | no           | ISO 8559-1 <br>(will be added) | SMPL <br>(will be added) | SMPL <br>(will be added) |

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
│   │   |   ├── scan.ply                # the same for FreeFusion
│   │   |   ├── model_smpl300.json      # the same for FreeFusion
│   │   |   ├── model_smpl300.ply       # the same for FreeFusion
│   │   |   └── measurements.csv        # the same for FreeFusion
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

![Portal MX](https://downloader.disk.yandex.ru/disk/7e85fe54bfedc2196fda58ac769a3a5313786e37edcc1fa9793dec646d50099b/682f4177/fKqInKw3d7bLFOeFnMGnhJMNXgaV5YxdHYR_N8px5j-iKVF5syM3E6C_ncqET9VXHY-WI2kQGjCTeXUFTLwW-RNq3gMbp1nkeEbswxpLHJ6r8npumZHI4midPdWhecNq?uid=0&filename=portal_mx.png&disposition=attachment&hash=uJHtLgPRVpznwVrLVDKp9TvCe5KFoxTReRiCy4X15vv7NZyn/Ch3%2BsoA4Oc3G107lsg4VIaLrfRKbQetv4dueQ%3D%3D%3A&limit=0&content_type=image%2Fpng&owner_uid=1130000067001764&fsize=2254489&hid=b0742c104081087baaa83164865ce71b&media_type=image&tknv=v3)

In opposite to it, Free Fusion is just an algorithm developed by TEXEL LLC in cooperation with Lomonosov Moscow State
University. It produces the same data (3D mesh, fitted SMPL, body measurements) using only one RGB-D ToF sensor. In
addition, the person being scanned can move freely, which greatly simplifies the scanning process. On the other hand,
these scans have coarse detail and introduce additional errors into the measurements.

![Free Fusion](https://downloader.disk.yandex.ru/disk/41abb0530854e7823a9bce8eeb4af2af3010b25fdbb8816a82692374d9255d17/682f41b8/fKqInKw3d7bLFOeFnMGnhOU6_l-2WFAz0LCoy7G1ifUJgvwrjH_CmR4vEjQG73JFUrBpxzHrRdSpParHhzgfJ3Vaq8Q4kdFd-61CXNA7T6Kr8npumZHI4midPdWhecNq?uid=0&filename=free_fusion.png&disposition=attachment&hash=uJHtLgPRVpznwVrLVDKp9XgokOl%2BBtEMmGnslXChVamwNUR7POM9hFSWTHrvCisWRmR/0fePyGwwW/WKW0/CEA%3D%3D%3A&limit=0&content_type=image%2Fpng&owner_uid=1130000067001764&fsize=1868583&hid=87f3951185e952cf790bdb8f4f1847bc&media_type=image&tknv=v3)

Depth maps and color frames from our dataset are the original records used by Free Fusion (not Portal MX!) to
reconstruct 3D meshes. The only fix was made to the depth maps was distortion mitigation using OpenCV.

## Direct links
To get our dataset, you can use the following links: [Part1](https://clck.ru/3MBJSu) (140 MB),
[Part2](https://clck.ru/3MCUYh) (935 MB). Since we are going to append new scans from time to time,
these direct links may become invalid. If this happens, visit our repo for the new ones.

## License
- **Dataset (depth maps, scans, annotations)**: [CC-BY-NC 4.0](LICENSE-DATA)
  (Free for non-commercial research; commercial use requires separate agreement).
- **Code (C++ parser)**: [MIT License](LICENSE-CODE)
  (Use freely, even commercially).
