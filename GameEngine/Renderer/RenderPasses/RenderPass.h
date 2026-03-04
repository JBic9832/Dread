#pragma once

class RenderPass {
public:
    virtual void Render() = 0;
    virtual void Setup() = 0;

private:
};