# Original Data (data/GHArchive)

Due to extremely large size, the data are stored at server 10.176.122.43:~/GitHub-Interaction-Graph/GHArchive.  
This fold only displays a sample file.

## Source
Open source data downloaded from `GitHub Archive`: https://www.gharchive.org/

## Size
54G (from 2019-01 to 2019-03)

## Format
All are seperated in different gz file by hour (e.g. 2019-01-17-6.json.gz), and each fz file contains only one json file, in which each line is a record of a user-triggered event.  
An example of a ForkEvent record:
```json
{
    "id":"11185281240",
    "type":"ForkEvent",
    "actor":{
        "id":13564443,
        "login":"fagan2888",
        "display_login":"fagan2888",
        "gravatar_id":"",
        "url":"https://api.github.com/users/fagan2888",
        "avatar_url":"https://avatars.githubusercontent.com/u/13564443?"
    },
    "repo":{
        "id":92406528,
        "name":"natashawatkins/linearmodels",
        "url":"https://api.github.com/repos/natashawatkins/linearmodels"
    },
    "payload":{ ... },
    "public":true,
    "created_at":"2020-01-01T00:00:00Z"
}

```