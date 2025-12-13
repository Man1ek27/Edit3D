#include "SceneObject.h"
#include "Matrix.h"

unsigned int SceneObject::currentId = 0;

SceneObject::SceneObject()
    : objectId(++currentId), name("Unnamed Object"), type(ObjectType::CUSTOM),
    position({ 0.0f, 0.0f, 0.0f }), rotation({ 0.0f, 0.0f, 0.0f }), scale({ 1.0f, 1.0f, 1.0f }),
    edgeColor(IM_COL32(255, 255, 255, 255)), vertexColor(IM_COL32(255, 0, 0, 255)),
    visible(true), selected(false) {
}

SceneObject::SceneObject(const std::string& name, ObjectType type)
    : objectId(++currentId), name(name), type(type),
    position({ 0.0f, 0.0f, 0.0f }), rotation({ 0.0f, 0.0f, 0.0f }), scale({ 1.0f, 1.0f, 1.0f }),
    edgeColor(IM_COL32(255, 255, 255, 255)), vertexColor(IM_COL32(255, 0, 0, 255)),
    visible(true), selected(false) {
}

SceneObject::SceneObject(const std::string& name, const ImVec3& position,
    const ImVec3& rotation, const ImVec3& scale, ObjectType type)
    : objectId(++currentId), name(name), type(type),
    position(position), rotation(rotation), scale(scale),
    edgeColor(IM_COL32(255, 255, 255, 255)), vertexColor(IM_COL32(255, 0, 0, 255)),
    visible(true), selected(false) {
}

ImVec3 SceneObject::TransformPoint(const ImVec3& local_point) const {
    // Utwórz macierze transformacji
    Matrix4x4 scaleMat = Matrix4x4::Scale(scale);
    Matrix4x4 rotationMat = Matrix4x4::RotationEuler(rotation.x, rotation.y, rotation.z);
    Matrix4x4 translationMat = Matrix4x4::Translation(position);

    // Z³o¿enie transformacji: T * R * S * point
    Matrix4x4 transform = translationMat.Multiply(rotationMat).Multiply(scaleMat);

    // Transformuj punkt
    return transform.TransformPoint(local_point);
}
