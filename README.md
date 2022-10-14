# OpenScience Dataverse API C library
This is a C library for the Dataverse API 



## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/aeonSolutions/OpenScience-Dataverse-API-C-library. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/libis/dataverse_api/blob/master/CODE_OF_CONDUCT.md).

## License

The library is available as open source under the terms of CC share alike non-commercial.

## Code of Conduct

Everyone interacting in the Dataverse API project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/libis/dataverse_api/blob/master/CODE_OF_CONDUCT.md).

### Coding standards

Please make sure tests pass before committing, and to add new tests for new additions.

## Progress

API | Endpoint | URL | Implemented ?| Notes 
------|----------|-----|--------------|-------
Native|Dataverses | - | Y| - 
| -   | -         | GET `api/dataverses/$id` | Y | -
| -   | -         | GET `` | N | -
| -   | -         | DELETE `api/dataverses/$id` | N | -
| -   | -         | POST `api/dataverses/$id/datasets` | N | -
| -   | -         | POST `api/dataverses/$identifier/actions/:publish` | N | -
Native|Datasets | POST `` | N| -
| -   | -         | GET `/api/datasets/$id/locks` | N | -
| -   | -         | DELETE `` | N | -
| -   | -         | GET `` | N | -
| -   | -         | GET `` | N | -
| -   | -         | POST `` | N | -
Native|MetadataBlocks | GET ` ` | N| -
| -   | -         | GET ` ` | N| -
Search | - | GET `` | N | All query params supported, optional data not returned yet.
Native | Upload file | POST `/api/datasets/:persistentId/add?persistentId=` | Y | - Add a file to a dataset
