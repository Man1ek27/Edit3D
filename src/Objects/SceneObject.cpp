#include "SceneObject.h"
#include "Matrix.h"

unsigned int SceneObject::currentId = 0;

SceneObject::SceneObject()
    : objectId(++currentId), name("Unnamed Object"), type(ObjectType::CUSTOM),
    position({ 0.0f, 0.0f, 0.0f }), rotation({ 0.0f, 0.0f, 0.0f }), scale({ 1.0f, 1.0f, 1.0f }),
    edgeColor(IM_COL32(255, 255, 255, 255)), vertexColor(IM_COL32(255, 0, 0, 255)),
    visible(true) {
}

SceneObject::SceneObject(const std::string& name, ObjectType type)
    : objectId(++currentId), name(name), type(type),
    position({ 0.0f, 0.0f, 0.0f }), rotation({ 0.0f, 0.0f, 0.0f }), scale({ 1.0f, 1.0f, 1.0f }),
    edgeColor(IM_COL32(255, 255, 255, 255)), vertexColor(IM_COL32(255, 0, 0, 255)),
    visible(true) {
}

SceneObject::SceneObject(const std::string& name, const ImVec3& position,
    const ImVec3& rotation, const ImVec3& scale, ObjectType type)
    : objectId(++currentId), name(name), type(type),
    position(position), rotation(rotation), scale(scale),
    edgeColor(IM_COL32(255, 255, 255, 255)), vertexColor(IM_COL32(255, 0, 0, 255)),
    visible(true) {
}

ImVec2 SceneObject::ProjectPoint(const ImVec3& point, const ImVec2& center, float scale, float zoom) {
    // Proste rzutowanie perspektywiczne
    float factor = 2.0f / (2.0f + point.z * zoom);
    float x = point.x * factor * scale;
    float y = point.y * factor * scale;

    return ImVec2(center.x + x, center.y - y); // Oœ Y jest odwrócona w oknie
}

// Pomocnicza funkcja do obracania punktu (kamera)
ImVec3 SceneObject::RotateCameraPoint(const ImVec3& point, float rotX, float rotY) {
    float radX = rotX * M_PI / 180.0f;
    float radY = rotY * M_PI / 180.0f;

    float cosX = std::cos(radX);
    float sinX = std::sin(radX);
    float cosY = std::cos(radY);
    float sinY = std::sin(radY);

    // Obrot wokó³ osi Y
    float x1 = point.x * cosY - point.z * sinY;
    float z1 = point.x * sinY + point.z * cosY;
    float y1 = point.y;

    // Obrot wokó³ osi X
    float y2 = y1 * cosX - z1 * sinX;
    float z2 = y1 * sinX + z1 * cosX;

    return ImVec3(x1, y2, z2);
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
