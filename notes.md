***
***
Iain Donald, barely 2026-03-08.
***

`License: BSD 3-Clause`.

# Notes

### Unsorted

- If run ... doesn't recognize the app name it will run the input text as a string, and add the app name (first word until space) as discoveredApps.txt and history.txt.


#### app structure

parseLine: builds apps map, and turns apps into: 

apps["cwebp"] =
{
    name = "cwebp",
    aliases = {"webp","webp_image_converter"},
    parameters = { {"url","string"} }
}