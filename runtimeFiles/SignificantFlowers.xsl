<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- Significant characters question updating -->
<!-- Import the identity transformation. -->

 <!--
   <xsl:import href="Identity.xsl"/>
  -->
   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>


    <!-- Mark question as deleted /ssn/p[@idx='27']/. -->


  <xsl:template match="ssn/p[@idx='6']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="concat('FM New',.)"/>
     </xsl:attribute>

    <xsl:attribute name="FM_newtagSIG">
     <xsl:value-of select="concat('FM New',.)"/>
   </xsl:attribute>

  </xsl:template>

  <xsl:template match="ssn/p[@idx='6']/respLs/respR/@*">


    <xsl:call-template name="XMLTOTITLE221" />


  </xsl:template>


<xsl:template name="XMLTOTITLE221">

 <xsl:for-each select=".">

        <xsl:choose>
              <!-- <xsl:when test="@respLS">-->
              <xsl:when test="position()  = 2">
                    <xsl:attribute name="{name()}">
                     <xsl:value-of select="concat('FM33 New ',.)"/>
                   </xsl:attribute>

              </xsl:when>

                 <!-- default 3 identifier cols -->
                 <xsl:otherwise>
                 <xsl:attribute name="{name()}">
                  <xsl:value-of select="concat('FM22 New ',.)"/>
                </xsl:attribute>
                 </xsl:otherwise>
           </xsl:choose>

 <xsl:attribute name="{name()}">
  <xsl:value-of select="concat('FM New ',.)"/>
</xsl:attribute>
<!--
   <replace_respA>
   <xsl:attribute name="{name()}">
    <xsl:value-of select="concat('FM New',.)"/>
   </xsl:attribute>

   <xsl:attribute name="qn">
    <xsl:value-of select="concat('FM New',.)"/>
  </xsl:attribute>
 </replace_respA>

    <v><xsl:value-of select="concat('FM-',.)" /></v>
    <c>ZZZZ</c>
    <xsl:element name="{name()}">
    </xsl:element>
-->

<!--
  <xsl:template match="ssn/p[@idx='6']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="concat('FM New',.)"/>
     </xsl:attribute>

    <xsl:attribute name="FM_newtagSIG">
     <xsl:value-of select="concat('FM New',.)"/>
   </xsl:attribute>

  </xsl:template>
  -->

 </xsl:for-each>

</xsl:template>


  <xsl:template match="ssn/p[@idx='6999']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="concat('FM New',.)"/>
     </xsl:attribute>
  </xsl:template>

  <xsl:template match="ssn/p[@idx='76']/@qn">
      <xsl:attribute name="qn">
       <xsl:value-of select="'fm-Yq'"/>
     </xsl:attribute>
  </xsl:template>

<!-- if not there lets add the attrib -->



  <xsl:template match="@nm">
     <xsl:attribute name="n">
       <xsl:value-of select="concat('new',.)"/>
     </xsl:attribute>
  </xsl:template>
</xsl:stylesheet>
