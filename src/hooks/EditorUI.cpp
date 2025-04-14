#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* p0) {
        if (!EditorUI::init(p0)) return false;
            
        auto menu = this->getChildByID("build-tabs-menu");

        
        auto spr = CCSprite::createWithSpriteFrameName("GJ_tabOff_001.png");
        
        spr->setID("background");
        if(this->getChildByID("edit-tabs-menu")) {
            auto menu2 = this->getChildByID("edit-tabs-menu");
            auto btn2 = CCMenuItemSpriteExtra::create(spr, this, menu_selector(MyEditorUI::moveBar));
            menu2->addChild(btn2);
            menu2->updateLayout();
        }
        auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(MyEditorUI::moveBar));
        menu->addChild(btn);
        btn->setID("reachability-button"_spr);
        auto arrowSpr = CCSprite::createWithSpriteFrameName("PBtn_Arrow_001.png");
        spr->addChild(arrowSpr);
        arrowSpr->setID("arrow-sprite"_spr);
        arrowSpr->setPosition({spr->getContentSize().width / 2, spr->getContentSize().height / 2});
        menu->updateLayout();

        return true;
    }

    struct Fields {
        std::unordered_map<cocos2d::CCNode*, cocos2d::CCPoint> movedNodes;
        bool isDown = false;
    };

    void moveBar(CCObject* sender) {
        m_fields->movedNodes.clear();
        auto dir = cocos2d::CCDirector::sharedDirector();
        m_fields->isDown = !m_fields->isDown;
        auto arrow = this->getChildByIDRecursive("arrow-sprite"_spr);
        arrow->runAction(CCEaseExponentialOut::create(CCRotateBy::create(1.f, 180.f)));

        for (auto& child : geode::cocos::CCArrayExt<CCNode*>(EditorUI::getChildren())) {
            cocos2d::CCPoint movement;
    
            if (child->getPositionY() < 91.f) {
                if(m_fields->isDown) {
                    movement = cocos2d::CCPoint{0.f, -90.f};
                    EditorUI::get()->m_toolbarHeight = 0.250f;
                }
                else {
                    movement = cocos2d::CCPoint{0.f, 90.f};
                    EditorUI::get()->m_toolbarHeight = 90.25f;
                }
            }

            child->runAction(CCEaseExponentialOut::create(CCMoveBy::create(1.f, movement)));
            m_fields->movedNodes[child] = movement;
        }
    }
};