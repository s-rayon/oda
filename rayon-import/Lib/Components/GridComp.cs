using System;
using System.Collections.Generic;
using System.Text;

namespace RayonImport.Lib.Components
{
    /// <summary>
    /// TODO : skip this for the time being
    /// </summary>
    internal class GridComp : ComponentValue
    {
        public override Component ToComponent(Element entity)
        {
            return new Component(entity, Component.ComponentTypeEnum.Grid, this);
        }
    }
}
