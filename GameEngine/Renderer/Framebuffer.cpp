#include "Framebuffer.h"

namespace Dread {

Framebuffer::Framebuffer(const int width, const int height)
	: m_Width { width }
	, m_Height { height } {
	glGenFramebuffers(1, &m_RendererId);
}

void Framebuffer::BindFramebuffer(const unsigned int target) const {
	glBindFramebuffer(target, m_RendererId);
}

void Framebuffer::SetColorFormat(const int internalColorFormat) {
	m_InternalColorFormat = internalColorFormat;
}

void Framebuffer::SetAttachment(const unsigned int attachment) {
	m_Attachment = attachment;
}

void Framebuffer::SetWidth(const int width) {
	m_Width = width;
	rebuildFramebuffer();
}

void Framebuffer::SetHeight(const int height) {
	m_Height = height;
	rebuildFramebuffer();
}

}
