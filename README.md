[![Telegram](https://img.shields.io/badge/join-telegram-blue.svg?style=for-the-badge)](https://t.me/+W4rVVa0_VLEzYmI0)
 [![WhatsApp](https://img.shields.io/badge/join-whatsapp-green.svg?style=for-the-badge)](https://chat.whatsapp.com/FkNC7u83kuy2QRA5sqjBVg) 
 [![Donate](https://img.shields.io/badge/donate-$-brown.svg?style=for-the-badge)](http://paypal.me/mtpsilva)
 [![Say Thanks](https://img.shields.io/badge/Say%20Thanks-!-yellow.svg?style=for-the-badge)](https://saythanks.io/to/mtpsilva)
![](https://img.shields.io/github/last-commit/aeonSolutions/openScienceResearch-Smart-DAQ-Device-able-to-Upload-Live-Experimental-Sensor-Data-to-a-Data-Repo?style=for-the-badge) <a href="https://trackgit.com">
<img src="https://us-central1-trackgit-analytics.cloudfunctions.net/token/ping/l98tfr0vje3q971a0cbl" alt="trackgit-views" />
</a>
![](https://views.whatilearened.today/views/github/aeonSolutions/OpenScience-Dataverse-API-C-library.svg)


# Open Science Dataverse API C library

[![](https://github.com/aeonSolutions/OpenScience-Dataverse-API-C-library/blob/main/dataverse_r_project.png)](https://dataverse.org)

This is a C library for the Dataverse API.

The Dataverse Project is an open-source web application to share, preserve, cite, explore, and analyze research data. It facilitates making data available to others and allows you to replicate others' work more easily. Researchers, journals, data authors, publishers, data distributors, and affiliated institutions all receive academic credit and web visibility. Funded by Harvard University and Powered by Open Scholar.

<br>
<br>

**Dataverse API in another coding language**

Goto dataverse.org for another coding language that best suits your coding style and needs. Currently there are client libraries for Python, Javascript, R, Java, and Julia that can be used to develop against Dataverse Software APIs

https://guides.dataverse.org/en/5.12/api/client-libraries.html

<br>
<br>

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/aeonSolutions/OpenScience-Dataverse-API-C-library. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/aeonSolutions/OpenScience-Dataverse-API-C-library/blob/main/CODE_OF_CONDUCT.md).

### Coding standards

Please make sure tests pass before committing, and to add new tests for new additions.

<br>
<br>

## Instalation & usage

To learn how to install and use this library, goto the wiki page [here](https://github.com/aeonSolutions/OpenScience-Dataverse-API-C-library/wiki) or by clicking on the top menu.

<br>
<br>

## Progress

<br>

API | Endpoint | URL | Implemented ?| Notes 
------|----------|-----|--------------|-------
Native|Dataverses | POST 'api/dataverses/$id' | Y| - 
| -   | -         | GET `api/dataverses/$id` | Y | -
| -   | -         | GET `api/dataverses/$id/contents` | N | -
| -   | -         | DELETE `api/dataverses/$id` | N | -
| -   | -         | POST `api/dataverses/$id/datasets` | N | -
| -   | -         | POST `api/dataverses/$identifier/actions/:publish` | N | -
Native|Datasets | GET `api/datasets/$id/versions` | N| -
| -   | -         | GET `/api/datasets/$id/locks` | Y | -  ✓Wiki
| -   | -         | DELETE `api/datasets/$id` | N | -
| -   | -         | POST `api/dataverses/$id` | N | -
| -   | -         | GET `PUT api/datasets/$id/versions/:draft?` | N | -
| -   | -         | POST `PUT api/datasets/$id/actions/:publish?type=$type` | N | -
Native|MetadataBlocks | GET `api/metadatablocks` | N| -
| -   | -         | GET ` api/metadatablocks/$identifier` | N| -
Search | - | GET `api/search` | N | -
Native | Upload file | POST `/api/datasets/:persistentId/add?persistentId=` | Y | Add a file to a dataset


<br />
<br />

______________________________________________________________________________________________________________________________
### License
2022 Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International

https://creativecommons.org/licenses/by-nc-sa/4.0/

______________________________________________________________________________________________________________________________

<br />
<br />

### Be supportive of my dedication and work towards technology and buy me a cup of coffee
Buy me a cup of coffee, a slice of pizza, or a book to help me study, eat and think of new functionalities to this library.

[<img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" data-canonical-src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="70" />](https://www.buymeacoffee.com/migueltomas)

<br />
<br />
