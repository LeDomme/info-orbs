#include "model/webDataElementTriangleModel.h"

int32_t WebDataElementTriangleModel::getX() {
    return m_x;
}

void WebDataElementTriangleModel::setX(int32_t x) {
    if (m_x != x) {
        m_x = x;
        m_changed = true;
    }
}

int32_t WebDataElementTriangleModel::getY() {
    return m_y;
}

void WebDataElementTriangleModel::setY(int32_t y) {
    if (m_y != y) {
        m_y = y;
        m_changed = true;
    }
}

int32_t WebDataElementTriangleModel::getX2() {
    return m_x2;
}

void WebDataElementTriangleModel::setX2(int32_t x) {
    if (m_x2 != x) {
        m_x2 = x;
        m_changed = true;
    }
}

int32_t WebDataElementTriangleModel::getY2() {
    return m_y2;
}

void WebDataElementTriangleModel::setY2(int32_t y) {
    if (m_y2 != y) {
        m_y2 = y;
        m_changed = true;
    }
}

int32_t WebDataElementTriangleModel::getX3() {
    return m_x3;
}

void WebDataElementTriangleModel::setX3(int32_t x) {
    if (m_x3 != x) {
        m_x3 = x;
        m_changed = true;
    }
}

int32_t WebDataElementTriangleModel::getY3() {
    return m_y3;
}

void WebDataElementTriangleModel::setY3(int32_t y) {
    if (m_y3 != y) {
        m_y3 = y;
        m_changed = true;
    }
}

void WebDataElementTriangleModel::setColor(int32_t color) {
    if (m_color != color) {
        m_color = color;
        m_changed = true;
    }
}

bool WebDataElementTriangleModel::getFilled() {
    return m_filled;
}

void WebDataElementTriangleModel::setFilled(bool filled) {
    if (m_filled != filled) {
        m_filled = filled;
        m_changed = true;
    }
}

void WebDataElementTriangleModel::setColor(String color) {
    setColor(Utils::stringToColor(color));
}

int32_t WebDataElementTriangleModel::getColor() {
    return m_color;
}

void WebDataElementTriangleModel::parseData(const JsonObject& doc, int32_t defaultColor, int32_t defaultBackground) {
    if (doc.containsKey("x1")) {
        setX(doc["x1"].as<int32_t>());
    } else if (doc.containsKey("x")) {
        setX(doc["x"].as<int32_t>());
    }
    if (doc.containsKey("y1")) {
        setY(doc["y1"].as<int32_t>());
    } else if (doc.containsKey("y")) {
        setY(doc["y"].as<int32_t>());
    }
    if (doc.containsKey("x2")) {
        setX2(doc["x2"].as<int32_t>());
    }
    if (doc.containsKey("y2")) {
        setY2(doc["y2"].as<int32_t>());
    }
    if (doc.containsKey("x3")) {
        setX3(doc["x3"].as<int32_t>());
    }
    if (doc.containsKey("y3")) {
        setY3(doc["y3"].as<int32_t>());
    }
    if (doc.containsKey("filled")) {
        setFilled(doc["filled"].as<bool>());
    }
    if (doc.containsKey("color")) {
        setColor(doc["color"].as<String>());
    } else {
        setColor(defaultColor);
    }
}

void WebDataElementTriangleModel::draw(TFT_eSPI& display) {
    if (getFilled()) {
        display.fillTriangle(getX(), getY(), getX2(), getY2(), getX3(), getY3(), getColor());
    } else {
        display.drawTriangle(getX(), getY(), getX2(), getY2(), getX3(), getY3(), getColor());
    }
}
