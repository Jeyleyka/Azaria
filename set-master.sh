#!/bin/bash

# Проверка, есть ли git
if ! command -v git &> /dev/null; then
    echo "❌ Git не установлен. Установи его сначала."
    exit 1
fi

echo "🔁 Переименование ветки main -> master"

# Переименование локальной ветки
git branch -m main master

# Пуш новой ветки на origin
git push -u origin master

# Удаление main из origin
git push origin --delete main

# Получение ссылки на репозиторий
REPO_URL=$(git config --get remote.origin.url)
REPO_URL_CLEAN=${REPO_URL%.git} # удаляет .git с конца

echo ""
echo "✅ Готово!"
echo "⚠️ Перейди по ссылке и сделай master дефолтной веткой вручную:"
echo "👉 $REPO_URL_CLEAN/settings/branches"
echo ""
echo "📌 После этого можно удалить main из интерфейса GitHub, если ещё осталась."
