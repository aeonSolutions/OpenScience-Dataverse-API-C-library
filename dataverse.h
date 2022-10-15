/*
   Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
   2022 Miguel Tomas
   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

    You are free to:
        Share — copy and redistribute the material in any medium or format
        Adapt — remix, transform, and build upon the material

    The licensor cannot revoke these freedoms as long as you follow the license terms.
    Under the following terms:
        Attribution                —  You must give appropriate credit, provide a link to the license, and indicate if 
                                      changes were made.You may do so in any reasonable manner, but not in any way that 
                                      suggests the licensor endorses you or your use.
        NonCommercial              —  You may not use the material for commercial purposes.
        ShareAlike                 —  If you remix, transform, or build upon the material, you must distribute your contributions
                                      under the same license as the original.

        No additional restrictions —  You may not apply legal terms or technological measures that legally restrict
                                      others from doing anything the license permits.

*/

#ifndef DATAVERSE_H
#define DATAVERSE_H


class Dataverse {
	
	public:
        // Max number of attempts for one particular HTTP request
        byte MAX_ATTEMPT_REQUESTS=5;
        
        // Class init
        Dataverse();

        // GET HTTP request to Dataverse: String url is the partial url
        String GetInfoFromDataverse(String url);

        // POST HTTP request to upload one file to a dataset located in $Persistant_Id
	    void UploadToDataverse() ;


	private:
        // POST HTTP request to upload one file to a dataset located in $Persistant_Id
        void UploadToDataverse(byte counter) ;
        // GET HTTP request to Dataverse: String url is the partial url; counter the number of request attepts tryed
        String GetInfoFromDataverse(String url, byte counter);
};


#endif