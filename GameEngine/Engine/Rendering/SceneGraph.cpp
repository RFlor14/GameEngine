#include "SceneGraph.h"

//redeclare static variables
std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

std::unordered_map<GLuint, std::vector<Model*>> SceneGraph::sceneModels =
    std::unordered_map<GLuint, std::vector <Model*>>();

std::map<std::string, GameObject*> SceneGraph::sceneGameObjects =
    std::map<std::string, GameObject*>();

SceneGraph::SceneGraph(){}

SceneGraph::~SceneGraph()
{
    OnDestroy();
}

SceneGraph* SceneGraph::GetInstance()
{
    /*
     Check's if the instance already exists,
     if not call reset on unique pointer.
    */
    if (sceneGraphInstance.get() == nullptr)
    {
        sceneGraphInstance.reset(new SceneGraph);
    }

    // Always return instance.get
    return sceneGraphInstance.get();
}


//Clears the two maps we created.
void SceneGraph::OnDestroy()
{

    
    /*
     First, clear out game object map.

     if statement helps so we dont get weird errors
     when destroying everything.

     for each object in the map, make sure pointers
     are being deleted, and also set it to nullptr.

     Then once its done going through the map, clear
     out the game object map.
    */
    if (sceneGameObjects.size() > 0)
    {
        for (auto go : sceneGameObjects)
        {
            delete go.second;
            go.second = nullptr;
        }

        sceneGameObjects.clear();
    }

    /*
     Second, clear out model map.

     Map also holds vector in it so it's a bit more work.

     For each entry of the model map, go into the vector
     of each entry.

     For each vector delete the pointer and set it to null,
     then clear out the vector.

     Then once it goes through everything, clear out the map.
    */
    if (sceneModels.size() > 0)
    {
        for (auto entry : sceneModels)
        {
            if (entry.second.size() > 0)
            {
                for (auto m : entry.second)
                {
                    delete m;
                    m = nullptr;
                }
                entry.second.clear();
           }
        }
        sceneModels.clear();
    }


}

void SceneGraph::AddModel(Model* model_)
{
    /*
     Save model's shader program to a temp GLuint,
     since we use it quite a bit.
    */
    GLuint shader = model_->GetShaderProgram();

    /*
     Find function will return the map.end (its an iterator
     that points to the end of the map), and return that
     if it didn't find what you're looking for.

     [if] it doesn't find the specific shader ID, we need to create
     this entry inside of the map.
    */
    if (sceneModels.find(shader) == sceneModels.end())
    {
        /*
         1) create an entry, we use the insert function.
         We have to declare the specific pair we're inserting.
         Inside the (), put in what you want your key and value to be.

         2) reserve some space for the vector.

         3) 
        */
        sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(
            shader, std::vector<Model*>()));
        sceneModels[shader].reserve(10);
    }

    /*
     regardless if the program ID exists in the map or not,
     go into the map and push back the specific model that
     we get passed in.
    */
    sceneModels[shader].push_back(model_);

}

void SceneGraph::AddGameObject(GameObject* go_, std::string tag_)
{
    /*
     [First scenario] 
     
     this tag = emptry string.

     Its possible the tag is empty, make sure we are creating some sort
     of tag for this game object.

     Once this tag is created, set gameobject's tag to this.

     Then go to the map and insert this new key/value pair.
    */
    if (tag_ == "")
    {
        std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
        go_->SetTag(newTag);
        sceneGameObjects[newTag] = go_;
    }

    /*
     [Second scenario]
     
     If the tag is not empty, make sure it doesn't exist inside 
     of the map, as it will override whatever value is associated
     with the key, we're good.

     Make sure the gam eobject has this tag set in its class
     variables. 
     
     Then, add the game object to the map.
    */
    else if (sceneGameObjects.find(tag_) == sceneGameObjects.end())
    {
        go_->SetTag(tag_);
        sceneGameObjects[tag_] = go_;
    }

    /*
     [Last Scenario]

     Tag is not empty, althogh it exists inside of the map,

     Follow the same thing we did in the [first scenario],

     Create a new tag, set game object's tag to this new tag,
     then add it to the map.
    */
    else
    {
        Debug::Error("Trying to add a GameObject with a tag " + tag_ +
            " that already exists", "SceneGraph.cpp", __LINE__);

        std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
        sceneGameObjects[newTag] = go_;
    }
}

GameObject* SceneGraph::GetGameObject(std::string tag_)
{
    /*
     If find function finds the specific tag that we're
     looking for, then return true (game object exists
     inside the map) so return the game object that's
     association with the tag.

     If we don't find the game object, inside the map,
     return nullptr.
    */
    if (sceneGameObjects.find(tag_) != sceneGameObjects.end())
    {
        return sceneGameObjects[tag_];
    }
    return nullptr;
}

void SceneGraph::Update(const float deltaTime_)
{
    /*
     Go through all of the game object inside
     of the scene graph's map and call update
     on every single one of them.
    */
    for (auto go : sceneGameObjects)
    {
        go.second->Update(deltaTime_);
    }
}

void SceneGraph::Render(Camera* camera_)
{
    /*
     Go through every entry inside of the model map
     (every entry is a different shader program),
     
     first change the OpenGL program that's being used
     using the glUseProgram function.

     Then go through all of the models and render all
     of the models.
    */
    for (auto entry : sceneModels)
    {
        glUseProgram(entry.first);
        for (auto m : entry.second)
        {
            m->Render(camera_);
        }
    }
}


