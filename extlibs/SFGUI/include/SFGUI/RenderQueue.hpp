#pragma once

#include <SFGUI/Config.hpp>
#include <SFGUI/Primitive.hpp>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>

namespace sf {
class Shape;
class Sprite;
class Text;
class VertexArray;
}

namespace sfg {

class RendererViewport;

/** Simple container for sf::Drawables.
 */
class SFGUI_API RenderQueue {
	public:
		/** Ctor.
		 */
		RenderQueue();

		/** Dtor.
		 */
		~RenderQueue();

		/** Add queue to this queue.
		 * Keep in mind that this queue takes ownership of the queue.
		 * @param queue Queue to add and manage.
		 */
		void Add( std::unique_ptr<RenderQueue> queue );

		void Add( Primitive::Ptr primitive );

		/** Get position of the drawable.
		 * @return Position of the drawable.
		 */
		const sf::Vector2f& GetPosition() const;

		/** Set position of the drawable.
		 * @param position Position.
		 */
		void SetPosition( const sf::Vector2f& position );

		/** Get the primitives in this queue.
		 * @return Primitives in this queue.
		 */
		const std::vector<Primitive::Ptr>& GetPrimitives() const;

		/** Get the Z layer this object should be rendered in.
		 * Larger values are rendered later. Default: 0.
		 * @return Z layer this object should be rendered in.
		 */
		int GetZOrder() const;

		/** Set the Z layer this object should be rendered in.
		 * Larger values are rendered later. Default: 0.
		 * @param z_order Z layer this object should be rendered in.
		 */
		void SetZOrder( int z_order );

		/** Draw this std::unique_ptr<RenderQueue>.
		 * @param show true to draw.
		 */
		void Show( bool show = true );

		/** Set draw hierarchy level of this std::unique_ptr<RenderQueue>.
		 * @param level Draw hierarchy level of this std::unique_ptr<RenderQueue>.
		 */
		void SetLevel( int level );

		/** Set viewport of this std::unique_ptr<RenderQueue>.
		 * @param viewport New viewport of this std::unique_ptr<RenderQueue>.
		 */
		void SetViewport( RendererViewport::Ptr viewport );

		/** Get viewport of this std::unique_ptr<RenderQueue>.
		 * @return Viewport of this std::unique_ptr<RenderQueue>.
		 */
		RendererViewport::Ptr GetViewport() const;

	private:
		std::vector<Primitive::Ptr> m_primitives;

		sf::Vector2f m_position;
		RendererViewport::Ptr m_viewport;

		int m_z_order;
		int m_level;

		bool m_show;
};

}
