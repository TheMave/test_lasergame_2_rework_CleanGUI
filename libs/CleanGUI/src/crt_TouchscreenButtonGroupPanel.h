#pragma once
#include <assert.h>
#include <crt_FreeRTOS.h>
#include "crt_typesAndConstants.h"
#include "crt_IDisplay.h"
#include "crt_Widget.h"
#include "crt_Panel.h"
#include "crt_ITouchListener.h"
#include <crt_IButton.h>

namespace crt
{
	template <size_t MaxNofChildren>
	class TouchscreenButtonGroupPanel : public Panel<MaxNofChildren>, public ITouchListener
	{
	private:
		ITouchListener* arTouchListener[MaxNofChildren] = {};
		uint16_t nofTouchListeners;

	public:
		using PBase = Panel<MaxNofChildren>;
		TouchscreenButtonGroupPanel(const char* strName, const Vec2& locPos, CoordType coordTypeLocPos,
			  const Vec2& size, int32_t cornerRadius, CoordType coordTypeSize, 
			  Alignment alignment, uint32_t colFg, uint32_t colBg) : 
			  PBase(strName, locPos, coordTypeLocPos,
				    size, cornerRadius, coordTypeSize, 
					alignment, colFg, colBg)
		{
		}

		// To add TouchscreenButtons or TouchscreenButtonGroupPanels, use the function below.
		// Pass the object twice. (because a reliable sideways-cast does not exist).
		void addTouchListener(IWidget& widget, ITouchListener& touchListener)
		{
			PBase::addChildWidget(widget);

			if (!isAlreadyPresent(&touchListener))
			{
				assert(nofTouchListeners < MaxNofChildren);
				arTouchListener[nofTouchListeners++] = &touchListener;
			}
		}

		/*override*/ bool addChildWidget(IWidget& widget)
		{
			assert((widget.getWidgetType() != WidgetType::TouchscreenButton) &&
				(widget.getWidgetType() != WidgetType::TouchscreenButtonGroupPanel));
			// If above asserts (it does so for TouchscreenButtons and TouchscreenButtonGroups),
			// you should have called addTouchListener instead.
			return PBase::addChildWidget(widget);
		}

		/* override */ WidgetType getWidgetType()
		{
			return WidgetType::TouchscreenButtonGroupPanel;
		}

		/*override*/ void setSizeOfParent(const Vec2& sizeOfParent)
		{
			PBase::setSizeOfParent(sizeOfParent);
			// A TouchScreenButtonGroup takes the size of its parent.
			// Typically, that could be a Panel.
			// This can be of importance if the buttons that are 
			// added to the TouchScreenButtonGroup use CoordType::Promillage
			// for its positions and/or sizes.
			//PBase::setSize(sizeOfParent, CoordType::Pixels);
		}

		// Forward the touchPressed events to the buttons in this buttongroup.
		/* override */ void touchPressed(const Vec2& pos)
		{
			if (!PBase::isEnabled())
			{
				return;
			}

			//ESP_LOGI("tsbg", "touch pressed", nof touch listeners: %d", nofTouchListeners);
			for (int i = 0; i < nofTouchListeners; i++)
			{
				arTouchListener[i]->touchPressed(pos);
			}
		}

		/* override */ void touchReleased(const Vec2& pos)
		{
			if (!PBase::isEnabled())
			{
				return;
			}

			//ESP_LOGI("tsbg", "touch released, nof touch listeners: %d", nofTouchListeners);
			for (int i = 0; i < nofTouchListeners; i++)
			{
				arTouchListener[i]->touchReleased(pos);
			}
		}

		/* override */ void show(bool bIncludeChildren)
		{
			PBase::show(bIncludeChildren);
		}

	private:
		bool isAlreadyPresent(ITouchListener * pTouchListener)
		{
			for (int i = 0; i < nofTouchListeners; i++)
			{
				//ESP_LOGI("adasdffasfsadf", "%s", i);
				if (arTouchListener[i] == pTouchListener)
				{
					return true;
				}
			}
			return false;
		}
	};
} // end namespace crt
