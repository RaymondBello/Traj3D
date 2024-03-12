#pragma once

class PerspectiveCamera
{
private:
    /* data */
public:
    PerspectiveCamera(/* args */);
    PerspectiveCamera(const PerspectiveCamera &other);
    PerspectiveCamera(PerspectiveCamera &&other) noexcept;
    PerspectiveCamera& operator=(const PerspectiveCamera &other);
    PerspectiveCamera& operator=(PerspectiveCamera &&other) noexcept;
    ~PerspectiveCamera();
};



