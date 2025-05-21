![LOGO](https://downloader.disk.yandex.ru/disk/8707c4793d2ca96d3ebb1d56b153dadf7b00bd7ca6018428b38ec8c875015ce9/682cdcdc/fKqInKw3d7bLFOeFnMGnhNu1lH1fCxoqUMmmvAYBWwskYp0WxpgQceQJXPDcpTOAmNM-fNKohGxDqPAcQ_fsVBtrfa8dXu5Cdd85ZbLDqoqr8npumZHI4midPdWhecNq?uid=0&filename=banner.png&disposition=attachment&hash=uJHtLgPRVpznwVrLVDKp9XPXXal%2BbAXqbP%2BaeljPEUOWEIEwmn97q0SdDzETy6QUDqZvSgIch5AN9ddz7ydViQ%3D%3D%3A&limit=0&content_type=image%2Fpng&owner_uid=1130000067001764&fsize=23348&hid=0560440144e485bf7df0768d0ff467bd&media_type=image&tknv=v3)

# Texel-BodyScan-Dataset
A dataset of 3D human body scans for non-commercial research, collected by TEXEL LLC and Lomonosov Moscow State University.
If you need much more, consider [commercial edition](https://texel.graphics/texel-3d-body-model-dataset/)
with thousands of these body scans.

## Structure

The presented scans were collected during various events under various conditions. Some persons
were consent to make their scans publicly available, while others choose to share only the depth
maps. To structure the dataset, we divided it into a few parts with the following characteristics:

|       | Number <br>of persons | Of which <br>men | Of which <br>women | Scans <br>per person   | Color <br>information | Total size |
| ----- | :-------------------: | :--------------: | :----------------: | :--------------------: | :-------------------: | :--------: |
| Part1 | 10                    | 5                | 5                  | 1                      | no                    | 200 MB     |
| Part2 | 42                    | 3                | 39                 | 5                      | no                    | 1.16 GB    |

Depending on the part number, the 'scan' word has a slightly different meaning. In general, it may
consist of a 3D body mesh, a SMPL/STAR parametric model fitted to it, automatic body measurements
and original RGB-D frames obtained from the depth sensor:

|       | Depth maps | Color frames | Measurements                   | Portal MX                | Free Fusion              |
| ----- | :--------: | :----------: | :----------------------------: | :----------------------: | :----------------------: |
| Part1 | yes        | no           | ISO 8559-1                     | 3D scan + SMPL           | 3D scan + SMPL           |
| Part2 | yes        | no           | ISO 8559-1 <br>(will be added) | SMPL <br>(will be added) | SMPL <br>(will be added) |

## Direct links
To get our dataset, you can use the following links: [Part1](https://clck.ru/3MBJSu) (140 MB),
[Part2](https://clck.ru/3MCUYh) (935 MB). Since we are going to append new scans from time to time,
these direct links may become invalid. If this happens, visit our repo for the new ones.

## License
- **Dataset (depth maps, scans, annotations)**: [CC-BY-NC 4.0](LICENSE-DATA)
  (Free for non-commercial research; commercial use requires separate agreement).
- **Code (C++ parser)**: [MIT License](LICENSE-CODE)
  (Use freely, even commercially).
