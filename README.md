# CampusGuide
The CampusData.json stores all the information of the map which will be shown in the application.
Any modifications of JSON subscripts should be applied under the following format:
## Header
```
    {
        "Transports":["vehicle", "people", "bicycle"],
        "LocationType":["scenery", "dormitory", "dinning", "shopping", "teaching", "administration", "complex", "others"]
    },
```
This part stores the information of Transport methods and Location type of the following dataset, which means "method" and "type" field of the following dataset could only contain the strings explicitly declared by this part.

## Main Dataset
```
    {
        "location":"// Location Name",
        "pos":[// Location's X-axis, // Location's Y-axis],
        "edges":[
            {
                "to":"// Destination of this edge",
                "method":[// Array, declare the transport mathod of this edge],
                "length":[// Array, declare the road length of each method mentioned above, must have the same length of "method"]
            }
        ],
        "type":[// Array, declare the scenery type of this location],
        "description":"Location Description",
        "level": //Integer, scenery level of this location
    },
```

Examples of the JSON subscript is shown in the JSON file.
