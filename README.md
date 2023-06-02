# CampusGuide
The CampusData.json stores all the information of the map which will be shown in the application.
Any modifications of JSON subscripts should be applied under the following format:
```
{
        "location":"LocationName",
        "pos":[X(double),Y(double)],
        "edges":[
            {
                "to":"LocationName(the other side of the edge of the graph)",
                "type":"Union of EdgeType(denote which transport method is allows, one of the following list:["people", "vehicle", "bicycle"])",
                "length":"1"
            },
            {
                (same as above)
            }
        ],
        "description":"LocationDescription",
        "level":(integer, scenery level of the location)
    },
```
Examples of the JSON subscript is shown in the JSON file.
