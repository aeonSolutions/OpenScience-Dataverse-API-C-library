# Open Science Dataverse API C library
This is a C library for the Dataverse API 



## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/aeonSolutions/OpenScience-Dataverse-API-C-library. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/aeonSolutions/OpenScience-Dataverse-API-C-library/blob/main/CODE_OF_CONDUCT.md).

## License

The library is available as open source under the terms of CC share alike non-commercial.


### Coding standards

Please make sure tests pass before committing, and to add new tests for new additions.

## Progress

API | Endpoint | URL | Implemented ?| Notes 
------|----------|-----|--------------|-------
Native|Dataverses | POST 'api/dataverses/$id' | Y| - 
| -   | -         | GET `api/dataverses/$id` | Y | -
| -   | -         | GET `api/dataverses/$id/contents` | N | -
| -   | -         | DELETE `api/dataverses/$id` | N | -
| -   | -         | POST `api/dataverses/$id/datasets` | N | -
| -   | -         | POST `api/dataverses/$identifier/actions/:publish` | N | -
Native|Datasets | GET `api/datasets/$id/versions` | N| -
| -   | -         | GET `/api/datasets/$id/locks` | Y | -
| -   | -         | DELETE `api/datasets/$id` | N | -
| -   | -         | POST `api/dataverses/$id` | N | -
| -   | -         | GET `PUT api/datasets/$id/versions/:draft?` | N | -
| -   | -         | POST `PUT api/datasets/$id/actions/:publish?type=$type` | N | -
Native|MetadataBlocks | GET `api/metadatablocks` | N| -
| -   | -         | GET ` api/metadatablocks/$identifier` | N| -
Search | - | GET `api/search` | N | All query params supported, optional data not returned yet.
Native | Upload file | POST `/api/datasets/:persistentId/add?persistentId=` | Y | - Add a file to a dataset
