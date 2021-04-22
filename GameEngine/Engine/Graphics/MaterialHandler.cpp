#include "MaterialHandler.h"

// Redeclaring static vars
std::unique_ptr<MaterialHandler> MaterialHandler::materialInstance = nullptr;
std::vector<Material> MaterialHandler::materials = std::vector<Material>();

MaterialHandler::MaterialHandler()
{
    // Reserve space in the vector
    materials.reserve(10);
}

MaterialHandler::~MaterialHandler()
{

    OnDestroy();
}

MaterialHandler* MaterialHandler::GetInstance()
{
    /*
     Check if instsance exist, if not (nulltpr)
     reset unique ptr.
    */
    if (materialInstance.get() == nullptr);
    {
        materialInstance.reset(new MaterialHandler);
    }

    return materialInstance.get();
}

void MaterialHandler::AddMaterial(Material& mat_)
{
    materials.push_back(mat_);
}

const Material MaterialHandler::GetMaterial(const std::string& matName_)
{
    /*
     Go through each element of the vector.

     Check to see if the name of that element = the
     name we pass in, then thats the mat we want to return.
    */
    for (auto mat : materials)
    {
        if (mat.name == matName_)
        {
            return mat;
        }
    }

    /*
     Not great to return material, as it may cause
     issues visually.

     Although, this makes sure we dont get any
     null errors.
    */
    return Material();
}

void MaterialHandler::OnDestroy()
{
    /*
     Since we're only holding vector of non pointer
     objects, we just need to tell it to clear.
    */
    if (materials.size() > 0)
    {
        materials.clear();
    }
}


