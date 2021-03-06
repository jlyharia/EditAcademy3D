
#include "Ea3dResource.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace Json;

Ea3dResource::Ea3dResource() {
    ifstream resource("setting.json", ifstream::binary);
    Reader reader;
    bool parsedSuccess = reader.parse(resource, this->rscRoot);
    if (!parsedSuccess) {
        // report to the user the failure and their locations in the document.
        cout << reader.getFormatedErrorMessages() << "\n";
    }
}

