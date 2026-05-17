cask "catchemailtools" do
  version "3.1"
  sha256 "1eb10f83515e1f4ce2275a28c6f32edcc07376143db628ac131b03551f71d508"

  url "https://github.com/Caspian-dev813/CatchEmailTools/releases/download/v#{version}/CatchEmailTools%20#{version}.zip"
  name "CatchEmailTools"
  desc "Email processing and management tools"
  homepage "https://github.com/Caspian-dev813/CatchEmailTools"

  app "CatchEmailTools.app"
end

