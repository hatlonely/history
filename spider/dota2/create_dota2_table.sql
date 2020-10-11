DROP DATABASE IF EXISTS dota2;
CREATE DATABASE IF NOT EXISTS dota2;
USE dota2;

CREATE TABLE hero (
    hero_id INT NOT NULL AUTO_INCREMENT,        -- 英雄id
    chinese_name VARCHAR(128) NOT NULL,         -- 中文名
    english_name VARCHAR(128) NOT NULL,         -- 英文名
    main_property CHAR(5) NOT NULL,             -- 主属性
    strength INT NOT NULL,                      -- 力量
    dexterity INT NOT NULL,                     -- 敏捷
    intelligence INT NOT NULL,                  -- 智力
    strength_inc DECIMAL(5, 2) NOT NULL,        -- 力量成长
    dexterity_inc DECIMAL(5, 2) NOT NULL,       -- 敏捷成长
    intelligence_inc DECIMAL(5, 2) NOT NULL,    -- 智力成长
    attack_min INT NOT NULL,                    -- 最低攻击力
    attack_max INT NOT NULL,                    -- 最高攻击力
    attack_speed INT NOT NULL,                  -- 攻击速度
    attack_range INT NOT NULL,                  -- 攻击范围
    armor INT NOT NULL,                         -- 护甲
    moving_speed INT NOT NULL,                  -- 移动速度
    visual_field_day INT NOT NULL,              -- 白天视野
    visual_field_night INT NOT NULL,            -- 晚上视野
    ballistic_velocity INT NOT NULL,            -- 弹道速度
    attack_type CHAR(5) NOT NULL,               -- 攻击类型
    position VARCHAR(64) NOT NULL,              -- 定位
    camp CHAR(5) NOT NULL,                      -- 阵营
    other_name VARCHAR(64) NOT NULL,            -- 其他名字
    story VARCHAR(2048) NOT NULL,               -- 故事背景
    icon VARCHAR(1024) NOT NULL,                -- 图标链接
    vert VARCHAR(1024) NOT NULL,                -- 大图标链接
    big_image VARCHAR(1024) NOT NULL,           -- 大图链接
    PRIMARY KEY(hero_id),
    UNIQUE KEY(chinese_name),
    UNIQUE KEY(english_name)
) DEFAULT CHARACTER SET UTF8;

CREATE TABLE abality (
    abality_id INT NOT NULL AUTO_INCREMENT,     -- 技能id
    hero_id INT NOT NULL,                       -- 英雄id
    idx INT NOT NULL,                           -- 属于英雄的第idx个技能
    chinese_name VARCHAR(10) NOT NULL,          -- 技能名
    icon VARCHAR(1024) NOT NULL,                -- 技能图标
    detail VARCHAR(1024) NOT NULL,              -- 技能说明
    notice VARCHAR(1024),                       -- 技能注意
    effect VARCHAR(1024),                       -- 技能效果
    scepter_effect VARCHAR(1024),               -- 神杖效果
    PRIMARY KEY(abality_id),
    UNIQUE KEY(hero_id, idx),
    FOREIGN KEY (hero_id) REFERENCES hero (hero_id) ON DELETE CASCADE
) DEFAULT CHARACTER SET UTF8;




