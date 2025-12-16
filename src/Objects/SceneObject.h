#pragma once
#include "PCH.h"

enum class ObjectType {
    BOX,
    SPHERE,
    CONE,
    LINE,
    CUSTOM
};

class SceneObject {
protected:
    static unsigned int currentId;
    unsigned int objectId;
    std::string commandRecord;

public:
    SceneObject();
    SceneObject(const std::string& name, ObjectType type = ObjectType::CUSTOM);
    SceneObject(const std::string& name, const ImVec3& position, const ImVec3& rotation,
        const ImVec3& scale, ObjectType type = ObjectType::CUSTOM);

    virtual ~SceneObject() = default;

	// Wirtualna metoda do rysowania obiektu - ka¿dy obiekt bêdzie implementowa³ j¹ inaczej
    virtual void Draw(ImDrawList* draw_list, const ImVec2& view_center, float view_scale,
        float cam_rotX, float cam_rotY, float cam_zoom,
        bool show_vertices = true, bool show_edges = true) const = 0;

    // Metoda do transformacji punktu lokalnego do œwiata
    virtual ImVec3 TransformPoint(const ImVec3& local_point) const;

    // Gettery
    std::string GetCommandRecord()const { return commandRecord; }
    unsigned int GetId() const { return objectId; }
    const std::string& GetName() const { return name; }
    ObjectType GetType() const { return type; }
    const ImVec3& GetPosition() const { return position; }
    const ImVec3& GetRotation() const { return rotation; }
    const ImVec3& GetScale() const { return scale; }
    const ImColor& GetEdgeColor() const { return edgeColor; }
    const ImColor& GetVertexColor() const { return vertexColor; }
    bool IsVisible() const { return visible; }
     
    // Settery
    void setCommandRecord(std::string command) { this->commandRecord = command; }
    void SetName(const std::string& name) { this->name = name; }
    void SetPosition(const ImVec3& position) { this->position = position; }
    void SetRotation(const ImVec3& rotation) { this->rotation = rotation; }
    void SetScale(const ImVec3& scale) { this->scale = scale; }
    void SetEdgeColor(const ImColor& color) { edgeColor = color; }
    void SetVertexColor(const ImColor& color) { vertexColor = color; }
    //mo¿e siê przydaæ przy clippingu
    void SetVisible(bool visible) { this->visible = visible; }

    // Transformacje
    void Translate(const ImVec3& translation) {
        position.x += translation.x;
        position.y += translation.y;
        position.z += translation.z;
    }

    void Rotate(const ImVec3& rotation_delta) {
        rotation.x += rotation_delta.x;
        rotation.y += rotation_delta.y;
        rotation.z += rotation_delta.z;
    }

    void Scale(const ImVec3& scale_factor) {
        scale.x *= scale_factor.x;
        scale.y *= scale_factor.y;
        scale.z *= scale_factor.z;
    }

    //Metoda do odœwierzania Wyœwietlanej komendy w rejestratorze
    virtual void reloadCommandRecord() = 0;
protected:
    // Dane obiektu
    std::string name;
    ObjectType type;
    ImVec3 position;
    ImVec3 rotation;  // w stopniach, Euler
    ImVec3 scale;
    ImColor edgeColor;
    ImColor vertexColor;
    bool visible;
};