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
Native|Dataverses | POST `api/dataverses/$id` | Y| - 
| -   | -         | GET `api/dataverses/$id` | Y | -
| -   | -         | GET `api/dataverses/$id/contents` | Y | -
| -   | -         | DELETE `api/dataverses/$id` | Y | -
| -   | -         | POST `api/dataverses/$id/datasets` | Y | -
| -   | -         | POST `api/dataverses/$identifier/actions/:publish` | Y | -
Native|Datasets | POST `api/dataverses/$id` | Y| -
| -   | -         | GET `api/datasets/$id` | Y | -
| -   | -         | DELETE `api/datasets/$id` | Y | -
| -   | -         | GET `api/datasets/$id/versions` | Y | -
| -   | -         | GET `PUT api/datasets/$id/versions/:draft?` | Y | -
| -   | -         | POST `PUT api/datasets/$id/actions/:publish?type=$type` | Y | -
Native|MetadataBlocks | GET ` api/metadatablocks` | Y| -
| -   | -         | GET ` api/metadatablocks/$identifier` | Y| -
Search | - | GET `api/search` | In progress | All query params supported, optional data not returned yet.
Sword | Upload file | 'Add files to a dataset with a zip file' | Y | -
